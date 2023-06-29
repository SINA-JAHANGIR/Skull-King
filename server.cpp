#include "server.h"
#include "ui_server.h"

#define BACK "QPushButton{border-image: url(:/photos/back-of-card.png);}"

server::server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    game_server = new QTcpServer();
    game_server->listen(QHostAddress::Any,1225);
    connect(game_server,SIGNAL(newConnection()),this,SLOT(connection_new()));
    game_server_page = new game(this);
    connect(game_server_page,SIGNAL(sig_send_card()),this,SLOT(slo_send_card()));
    connect(game_server_page,SIGNAL(sig_send_one_card(card)),this,SLOT(slo_send_one_card(card)));
    connect(game_server_page,SIGNAL(sig_change_card()),this,SLOT(slo_change_card()));
    connect(this,SIGNAL(sig_change_request()),this,SLOT(slo_change_request()));
    connect(game_server_page,SIGNAL(sig_send_forecast()),this,SLOT(slo_send_forecast()));
    connect(this,SIGNAL(sig_game_continue()),&game_server_page->loop,SLOT(quit()));
}

server::~server()
{
    thread.join();
    delete ui;
}

void server::connection_new(){
    client_socket = game_server->nextPendingConnection();
    //this->ui->btn_start->setEnabled(true);
    thread = std::thread(&server::slo_read_card,this);
    spy = new QSignalSpy(this,SIGNAL(sig_continue()));
    ready = true;
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
    spy->wait(-1);
//    QByteArray temp2 = client_socket->readAll();
    QString card_num = QString::number(n);
    client_socket->write(card_num.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
    spy->wait(-1);
//    temp2 = client_socket->readAll();
    card_num = QString::number(m);
    client_socket->write(card_num.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
    spy->wait(-1);
//    temp2 = client_socket->readAll();
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
    while(true)
    {
        static int n =0 ;
        while(client_socket->waitForReadyRead(-1))
        {
            received = client_socket->readAll();
            if(received == "ok")
            {
                emit sig_continue();
                received.clear();
                n++;
            }
            else if(received == "change_request")
            {
                QString t ="ok";
                client_socket->write(t.toStdString().c_str());
                client_socket->waitForBytesWritten(-1);
                received.clear();
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
        }
    }
}

void server::slo_change_card()
{
    QString temp = "change_request";
    client_socket->write(temp.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
}

void server::slo_change_request()
{
    QMessageBox msbox;
    QPushButton *accept = msbox.addButton(tr("Accept"),QMessageBox::ActionRole);
    QPushButton *reject = msbox.addButton(tr("Reject"),QMessageBox::ActionRole);

    msbox.exec();
    if(msbox.clickedButton() == accept)
    {
        //accept
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
