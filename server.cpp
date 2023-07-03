#include "server.h"
#include "ui_server.h"
#include <QScreen>
#include <windows.h>

#define BACK "QPushButton{border-image: url(:/photos/back-of-card.png);}"
const int w = 100 , a = (600/400) , h = a*w;

server::server(person per1,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    par = parent;
    person1 = per1;
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
    game_server = new QTcpServer();
    game_server->listen(QHostAddress::Any,1225);
    game_server->setMaxPendingConnections(1);
    connect(game_server,SIGNAL(newConnection()),this,SLOT(connection_new()));
    person1.set_coin(person1.get_coin()-50);
    game_server_page = new game(person1,par);
    game_server_page->setWindowTitle("Skull King");
    connect(game_server_page,SIGNAL(sig_send_card()),this,SLOT(slo_send_card()));
    connect(game_server_page,SIGNAL(sig_send_one_card(card)),this,SLOT(slo_send_one_card(card)));
    connect(game_server_page,SIGNAL(sig_change_card()),this,SLOT(slo_change_card()));
    connect(this,SIGNAL(sig_change_request()),this,SLOT(slo_change_request()));
    connect(game_server_page,SIGNAL(sig_send_forecast()),this,SLOT(slo_send_forecast()));
//    connect(this,SIGNAL(sig_game_continue()),&game_server_page->loop,SLOT(quit()));
    connect(this,SIGNAL(sig_game_continue()),game_server_page,SLOT(slo_selected_p2_card_btn()));
    connect(game_server_page,SIGNAL(sig_end_of_round()),this,SLOT(slo_end_of_round()));
    connect(this,SIGNAL(sig_get_forecast()),&game_server_page->start,SLOT(quit()));

    connect(game_server_page,SIGNAL(sig_stop()),this,SLOT(slo_stop()));
    connect(game_server_page,SIGNAL(sig_resume()),this,SLOT(slo_resume()));
    connect(this,SIGNAL(sig_stop()),game_server_page,SLOT(slo_stop()));
    connect(this,SIGNAL(sig_resume()),game_server_page,SLOT(slo_resume()));

    connect(game_server_page,SIGNAL(sig_exit()),this,SLOT(slo_exit()));
    connect(this,SIGNAL(sig_exit()),game_server_page,SLOT(slo_exit()));
}

server::~server()
{
    thread.join();
    delete ui;
}

void server::connection_new(){

    if(num_player < 2)
    {
        num_player++;
        client_socket = game_server->nextPendingConnection();
        connect(client_socket,SIGNAL(readyRead()),this,SLOT(slo_read_card()));
        this->ui->btn_start->setEnabled(true);
        ui->label->setText(client_socket->localAddress().toString() + " Connected");
        thread = std::thread(&server::slo_read_card,this);
        spy = new QSignalSpy(this,SIGNAL(sig_continue()));
        ready = true;
        QString t = "username";
        client_socket->write(t.toStdString().c_str());
        client_socket->waitForBytesWritten(1000);
    }
    else
    {
        QTcpSocket *client = new QTcpSocket();
        client = game_server->nextPendingConnection();
        client->write("Server is full.");
        client->waitForBytesWritten(1000);
        client->close();
        client->deleteLater();
    }
}


QByteArray server::card_to_qbytearray(const card& input){
    QByteArray output;
    QDataStream stream(&output, QIODevice::ReadWrite);
    stream <<input.get_type()<<input.get_value()<<input.get_selected()<<input.get_number();

    return output;
}
card server::qbytearray_to_card(QByteArray& input)
{
    card output;
    QDataStream stream(&input, QIODevice::ReadWrite);

    card_type type;
    int value;
    bool selected;
    int number;
    stream >>type>>value>>selected>>number;

    output.set_type(type);
    output.set_value(value);
    output.set_selected(selected);
    output.set_number(number);

    return output;
}

void server::change_card()
{
    int n = rand() % game_server_page->player1.cards.size();
    int m = rand() % game_server_page->player2.cards.size();
    iter it_p1 = game_server_page->player1.find_card(game_server_page->player1.cards[n]);
    iter it_p2 = game_server_page->player2.find_card(game_server_page->player2.cards[m]);
    customized_button* bp1 = *it_p1;
    customized_button* bp2 = *it_p2;
    game_server_page->player1.cards.erase(it_p1);
    game_server_page->player2.cards.erase(it_p2);
    game_server_page->player1.cards.append(bp2);
    game_server_page->player2.cards.append(bp1);
    bp2->change_card_StyleSheet();
    bp1->setStyleSheet(BACK);
    bp1->setEnabled(false);

    QString t = "change";
    client_socket->write(t.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
    client_socket->waitForReadyRead(-1);
    QByteArray temp2 = client_socket->readAll();
    QString card_num = QString::number(n);
    client_socket->write(card_num.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
    client_socket->waitForReadyRead(-1);
    temp2 = client_socket->readAll();
    card_num = QString::number(m);
    client_socket->write(card_num.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
    client_socket->waitForReadyRead(-1);
    temp2 = client_socket->readAll();

    game_server_page->clear_move_animations();
    QPropertyAnimation *animation = new QPropertyAnimation(bp2,"geometry");
    animation->setDuration(700);
    QRect temp = bp2->geometry();
    animation->setStartValue(temp);
    animation->setEndValue(QRect((game_server_page->width()/2-w/2), game_server_page->height()-h-90, w, h));
    game_server_page->all_move_animation.append(animation);
    animation->start();

    QPropertyAnimation *animation2 = new QPropertyAnimation(bp1,"geometry");
    animation2->setDuration(700);
    QRect temp3 = bp1->geometry();
    animation2->setStartValue(temp3);
    animation2->setEndValue(QRect((game_server_page->width()/2-w/2), 60, w, h));
    game_server_page->all_move_animation.append(animation2);
    animation2->start();

    connect(animation2,SIGNAL(finished()),this,SLOT(slo_finish_animation()));
}

void server::on_btn_start_clicked()
{
    // if (ready)
    // {
           this->close();
           game_server_page->show();
           game_server_page->game_server_start();
    // }
}

void server::slo_send_card()
{
    QString t ="send cards";
    client_socket->write(t.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
}

void server::slo_send_one_card(card input)
{
    QString t ="selected";
    client_socket->write(t.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
}

void server::slo_read_card()
{
    QByteArray received;
//    while(true)
//    {
        static int n =0 ;
//        while(client_socket->waitForReadyRead(-1))
//        {
            received = client_socket->readAll();
            if(received == "ok")
            {
                emit sig_continue();
                received.clear();
                n++;
            }
            else if(received == "change_request")
            {
                emit sig_change_request();
            }
            else if(received == "ready")
            {
                QString t = "player1";
                for( int i=0 ; i < game_server_page->player2.cards.size() ; i++ )
                {
                    client_socket->write(t.toStdString().c_str());
                    client_socket->waitForBytesWritten(-1);
                    client_socket->waitForReadyRead(-1);
                    QByteArray temp2 = client_socket->readAll();
                    customized_button* temp = game_server_page->player2.cards[i];
                    QByteArray card_byte = card_to_qbytearray(temp->get_btn_card());
                    client_socket->write(card_byte);
                    client_socket->waitForBytesWritten(-1);
                    client_socket->waitForReadyRead(-1);
                    temp2 = client_socket->readAll();
                }
                t = "player2";
                for( int i=0 ; i < game_server_page->player1.cards.size() ; i++ )
                {
                    client_socket->write(t.toStdString().c_str());
                    client_socket->waitForBytesWritten(-1);
                    client_socket->waitForReadyRead(-1);
                    QByteArray temp2 = client_socket->readAll();
                    customized_button* temp = game_server_page->player1.cards[i];
                    QByteArray card_byte = card_to_qbytearray(temp->get_btn_card());
                    client_socket->write(card_byte);
                    client_socket->waitForBytesWritten(-1);
                    client_socket->waitForReadyRead(-1);
                    temp2 = client_socket->readAll();
                }
                t="end";
                client_socket->write(t.toStdString().c_str());
                client_socket->waitForReadyRead(-1);
                QByteArray temp2 = client_socket->readAll();
                temp2.clear();
                game_server_page->wait = false;
            }
            else if(received == "forecast")
            {
                QString temp = "send forecast";
                client_socket->write(temp.toStdString().c_str());
                client_socket->waitForBytesWritten(-1);
                client_socket->waitForReadyRead(-1);
                QByteArray temp2 = client_socket->readAll();
                game_server_page->player2.set_forecast_number(temp2.toInt());
                emit sig_get_forecast();
            }
            else if(received == "send forecast")
            {
                QString temp = QString::number(game_server_page->player1.get_forecast_number());
                client_socket->write(temp.toStdString().c_str());
                client_socket->waitForBytesWritten(-1);
            }
            else if(received=="selected")
            {
                QString message = "send one card";
                client_socket->write(message.toStdString().c_str());
                client_socket->waitForBytesWritten(-1);
                client_socket->waitForReadyRead(-1);
                QByteArray card_byte =  client_socket->readAll();
                card temp = qbytearray_to_card(card_byte);
                game_server_page->player2.set_selected_card_btn(game_server_page->all_cards_btn[temp.get_number()]);
                //...

                received.clear();
                message = "readed";
                client_socket->write(message.toStdString().c_str());
                client_socket->waitForBytesWritten(-1);
                emit sig_game_continue();
            }
            else if( received=="send one card")
            {
                QByteArray card_byte = card_to_qbytearray(game_server_page->player1.get_selected_card_btn()->get_btn_card());
                client_socket->write(card_byte);
                client_socket->waitForBytesWritten(-1);
                client_socket->waitForReadyRead(-1);
                QByteArray temp2 = client_socket->readAll();
            }
            else if(received == "username")
            {
                QString un = game_server_page->player1.get_username();
                client_socket->write(un.toStdString().c_str());
                client_socket->waitForBytesWritten(-1);
                client_socket->waitForReadyRead(-1);
                QString temp2 = client_socket->readAll();
                game_server_page->player2.set_username(temp2);
                game_server_page->lbl_username_p2->setText(game_server_page->player2.get_username());
            }
            else if(received == "reject")
            {
                QMessageBox::information(game_server_page,"Skull King",game_server_page->player2.get_username() +" rejected your request");
            }
            else if(received == "accept")
            {
                game_server_page->inactive_card_click();
                change_card();
            }
            else if(received == "Stop")
            {
                emit sig_stop();
            }
            else if(received == "Resume")
            {
                emit sig_resume();
            }
            else if(received == "Exit")
            {
                emit sig_exit();
            }
//        }
//    }
}

void server::slo_change_card()
{
    QString temp = "change_request";
    client_socket->write(temp.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
}

void server::slo_change_request()
{
    QMessageBox msbox(game_server_page);
    msbox.setText( game_server_page->player2.get_username() + " has requested to exchange a card with you .");
    QPushButton *accept = msbox.addButton(tr("Accept"),QMessageBox::ActionRole);
    QPushButton *reject = msbox.addButton(tr("Reject"),QMessageBox::ActionRole);

    msbox.exec();
    if(msbox.clickedButton() == accept)
    {
        //accept
        game_server_page->inactive_card_click();
        change_card();
        msbox.close();
    }
    else if(msbox.clickedButton() == reject)
    {
        //reject
        QString temp = "reject";
        client_socket->write(temp.toStdString().c_str());
        client_socket->waitForBytesWritten(-1);
        msbox.close();
    }
}

void server::slo_send_forecast()
{
    QString temp = "forecast";
    client_socket->write(temp.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
}

void server::slo_end_of_round()
{
    game_server_page->make_card(game_server_page->r);
}

void server::slo_finish_animation()
{
    game_server_page->sort_btn_cards(game_server_page->player1.cards);
    game_server_page->rasie_p1_cards();
    game_server_page->slo_p1_arrange_card();
    game_server_page->sort_btn_cards(game_server_page->player2.cards);
    game_server_page->rasie_p2_cards();
    game_server_page->slo_p2_arrange_card();
    if(game_server_page->turn == p1)
    {
        game_server_page->slo_active_card_click();
    }
}

void server::slo_stop()
{
    QString temp = "Stop";
    client_socket->write(temp.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
}

void server::slo_resume()
{
    QString temp = "Resume";
    client_socket->write(temp.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
}

void server::slo_exit()
{
    QString temp = "Exit";
    client_socket->write(temp.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
}
