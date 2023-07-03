#include "client.h"
#include "ui_client.h"
#include "ui_game.h"
#include <QScreen>
#include <windows.h>

#define BACK "QPushButton{border-image: url(:/photos/back-of-card.png);}"
const int w = 100 , a = (600/400) , h = a*w;

client::client(person per1,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    par = parent;
    person1 = per1;
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
    socket = new QTcpSocket;

    person1.set_coin(person1.get_coin()-50);
    game_client_page = new game(person1,par);
    game_client_page->setWindowTitle("Skull King");
    connect(game_client_page,SIGNAL(sig_send_one_card(card)),this,SLOT(slo_send_one_card(card)));
    connect(game_client_page,SIGNAL(sig_change_card()),this,SLOT(slo_change_card()));
    connect(this,SIGNAL(sig_change_request()),this,SLOT(slo_change_request()));
    thread = std::thread(&client::slo_read_card,this);
//    spy = new QSignalSpy(this,SIGNAL(sig_continue()));
//    connect(this,SIGNAL(sig_game_continue()),&game_client_page->loop,SLOT(quit()));
    connect(this,SIGNAL(sig_game_continue()),game_client_page,SLOT(slo_selected_p2_card_btn()));
    connect(game_client_page,SIGNAL(sig_send_forecast()),this,SLOT(slo_send_forecast()));
    connect(this,SIGNAL(sig_start()),this,SLOT(slo_call_dealer_animation()));
    connect(this,SIGNAL(sig_get_forecast()),&game_client_page->start,SLOT(quit()));

    connect(game_client_page,SIGNAL(sig_stop()),this,SLOT(slo_stop()));
    connect(game_client_page,SIGNAL(sig_resume()),this,SLOT(slo_resume()));
    connect(this,SIGNAL(sig_stop()),game_client_page,SLOT(slo_stop()));
    connect(this,SIGNAL(sig_resume()),game_client_page,SLOT(slo_resume()));

    connect(game_client_page,SIGNAL(sig_exit()),this,SLOT(slo_exit()));
    connect(this,SIGNAL(sig_exit()),game_client_page,SLOT(slo_exit()));
}

client::~client()
{
    thread.join();
    delete ui;
}

void client::on_pushButton_clicked()
{
    QString ip_address = ui->line_ip->text();
    socket->connectToHost(ip_address,1225);
    connect(socket,SIGNAL(connected()),this,SLOT(connected_to_server()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(slo_read_card()));
}

void client::connected_to_server()
{
    ui->pushButton->setEnabled(false);
    ui->label->setText("Connected to server");
}


QByteArray client::card_to_qbytearray(const card& input){
    QByteArray output;
    QDataStream stream(&output, QIODevice::ReadWrite);
    stream <<input.get_type()<<input.get_value()<<input.get_selected()<<input.get_number();

    return output;
}
card client::qbytearray_to_card(QByteArray& input)
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

void client::slo_read_card()
{
        QString t ="ok";
//    while(true)
//    {
//        while(socket->waitForReadyRead(-1))
//        {
            QByteArray received = socket->readAll();
            if(received=="end")
            {
                emit sig_start();
                socket->write(t.toStdString().c_str());
                socket->waitForBytesWritten(-1);
            }
            else if(received == "send cards")
            {
                QString t2 ="ready";
                socket->write(t2.toStdString().c_str());
                socket->waitForBytesWritten(-1);
            }
            else if(received=="player1")
            {
                socket->write(t.toStdString().c_str());
                socket->waitForBytesWritten(-1);
                socket->waitForReadyRead(-1);
                QByteArray card_byte = socket->readAll();
                card temp = qbytearray_to_card(card_byte);
                game_client_page->player1.cards.append(game_client_page->all_cards_btn[temp.get_number()]);
                game_client_page->all_cards_btn[temp.get_number()]->setParent(game_client_page->ui->centralwidget);
                game_client_page->all_cards_btn[temp.get_number()]->show();
                game_client_page->all_cards_btn[temp.get_number()]->change_card_StyleSheet();
                socket->write(t.toStdString().c_str());
                socket->waitForBytesWritten(-1);
            }
            else if(received=="player2")
            {
                socket->write(t.toStdString().c_str());
                socket->waitForBytesWritten(-1);
                socket->waitForReadyRead(-1);
                QByteArray card_byte = socket->readAll();
                card temp = qbytearray_to_card(card_byte);
                game_client_page->player2.cards.append(game_client_page->all_cards_btn[temp.get_number()]);
                game_client_page->all_cards_btn[temp.get_number()]->setParent(game_client_page->ui->centralwidget);
                game_client_page->all_cards_btn[temp.get_number()]->show();
                game_client_page->all_cards_btn[temp.get_number()]->setStyleSheet(BACK);
                socket->write(t.toStdString().c_str());
                socket->waitForBytesWritten(-1);

                if(game_client_page->r == 0)
                {
                    if(game_client_page->player1.cards[0]->get_btn_card() > game_client_page->player2.cards[0]->get_btn_card())
                    {
                        game_client_page->turn = p1;
                    }
                    else
                    {
                        game_client_page->turn = p2;
                    }
                    this->hide();
                    game_client_page->show();
                    game_client_page->game_client_start();
                }
            }
            else if(received=="selected")
            {
                QString message = "send one card";
                socket->write(message.toStdString().c_str());
                socket->waitForBytesWritten(-1);
                socket->waitForReadyRead(-1);
                QByteArray card_byte = socket->readAll();
                card temp = qbytearray_to_card(card_byte);
                game_client_page->player2.set_selected_card_btn(game_client_page->all_cards_btn[temp.get_number()]);
                //...
                message = "readed";
                socket->write(message.toStdString().c_str());
                socket->waitForBytesWritten(-1);
                emit sig_game_continue();
            }
            else if( received=="send one card")
            {
                QByteArray card_byte = card_to_qbytearray(game_client_page->player1.get_selected_card_btn()->get_btn_card());
                socket->write(card_byte);
                socket->waitForBytesWritten(-1);
                socket->waitForReadyRead(-1);
                QByteArray temp2 = socket->readAll();
            }
            else if(received=="change")
            {
                game_client_page->inactive_card_click();
                socket->write(t.toStdString().c_str());
                socket->waitForBytesWritten(-1);
                socket->waitForReadyRead(-1);
                QByteArray card_number = socket->readAll();
                int q = card_number.toInt();
                socket->write(t.toStdString().c_str());
                socket->waitForBytesWritten(-1);
                socket->waitForReadyRead(-1);
                card_number = socket->readAll();
                int p = card_number.toInt();
                //change ...
                iter it_p2 = game_client_page->player2.find_card(game_client_page->player2.cards[q]);
                iter it_p1 = game_client_page->player1.find_card(game_client_page->player1.cards[p]);
                customized_button* bp2 = *it_p2;
                customized_button* bp1 = *it_p1;
                game_client_page->player2.cards.erase(it_p2);
                game_client_page->player1.cards.erase(it_p1);
                game_client_page->player2.cards.append(bp1);
                game_client_page->player1.cards.append(bp2);
                bp2->change_card_StyleSheet();
                bp1->setEnabled(false);
                bp1->setStyleSheet(BACK);
                socket->write(t.toStdString().c_str());
                socket->waitForBytesWritten(-1);

                game_client_page->clear_move_animations();
                QPropertyAnimation *animation = new QPropertyAnimation(bp2,"geometry");
                animation->setDuration(700);
                QRect temp = bp2->geometry();
                animation->setStartValue(temp);
                animation->setEndValue(QRect((game_client_page->width()/2-w/2), game_client_page->height()-h-90, w, h));
                game_client_page->all_move_animation.append(animation);
                animation->start();

                QPropertyAnimation *animation2 = new QPropertyAnimation(bp1,"geometry");
                animation2->setDuration(700);
                QRect temp3 = bp1->geometry();
                animation2->setStartValue(temp3);
                animation2->setEndValue(QRect((game_client_page->width()/2-w/2), 60, w, h));
                game_client_page->all_move_animation.append(animation2);
                animation2->start();

                connect(animation2,SIGNAL(finished()),this,SLOT(slo_finish_animation()));
            }
            else if(received == "change_request")
            {
                emit sig_change_request();
            }
            else if(received == "forecast")
            {
                QString temp = "send forecast";
                socket->write(temp.toStdString().c_str());
                socket->waitForBytesWritten(-1);
                socket->waitForReadyRead(-1);
                QByteArray temp2 = socket->readAll();
                game_client_page->player2.set_forecast_number(temp2.toInt());
                emit sig_get_forecast();
            }
            else if(received == "send forecast")
            {
                QString temp = QString::number(game_client_page->player1.get_forecast_number());
                socket->write(temp.toStdString().c_str());
                socket->waitForBytesWritten(-1);
            }
            else if(received == "reject")
            {
                QMessageBox::information(game_client_page,"Skull King",game_client_page->player2.get_username() +" rejected your request !");
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
            else if(received == "ok")
            {
                emit sig_continue();
            }
            else if(received == "username")
            {
                QString un ="username";
                socket->write(un.toStdString().c_str());
                socket->waitForBytesWritten(-1);
                socket->waitForReadyRead(-1);
                QString temp2 = socket->readAll();
                game_client_page->player2.set_username(temp2);
                un = game_client_page->player1.get_username();
                socket->write(un.toStdString().c_str());
                socket->waitForBytesWritten(-1);
                game_client_page->lbl_username_p2->setText(game_client_page->player2.get_username());
            }
            else if(received == "Server is full.")
            {
                ui->label->setText("Server is full");
                QMessageBox::information(this,"Connection error","Server is full");
                socket->disconnectFromHost();
            }
//        }
//    }
}

void client::slo_send_one_card(card input)
{
    QString t ="selected";
    socket->write(t.toStdString().c_str());
    socket->waitForBytesWritten(-1);

}

void client::slo_change_card()
{
    QString temp = "change_request";
    socket->write(temp.toStdString().c_str());
    socket->waitForBytesWritten(-1);
}

void client::slo_send_forecast()
{
    QString temp = "forecast";
    socket->write(temp.toStdString().c_str());
    socket->waitForBytesWritten(-1);
}

void client::slo_call_dealer_animation()
{
    if(game_client_page->r>0)
    {
        game_client_page->sort_btn_cards(game_client_page->player1.cards);
        game_client_page->sort_btn_cards(game_client_page->player2.cards);
        game_client_page->rasie_p2_cards();
        game_client_page->rasie_p1_cards();
    }
    game_client_page->dealer_animation();
}

void client::slo_finish_animation()
{
    game_client_page->sort_btn_cards(game_client_page->player1.cards);
    game_client_page->rasie_p1_cards();
    game_client_page->slo_p1_arrange_card();
    game_client_page->sort_btn_cards(game_client_page->player2.cards);
    game_client_page->rasie_p2_cards();
    game_client_page->slo_p2_arrange_card();
    if(game_client_page->turn == p1)
    {
        game_client_page->slo_active_card_click();
    }
}

void client::slo_change_request()
{
    QMessageBox msbox(game_client_page);
    msbox.setText(game_client_page->player2.get_username() + " has requested to exchange a card with you .");
    QPushButton *accept = msbox.addButton(tr("Accept"),QMessageBox::ActionRole);
    QPushButton *reject = msbox.addButton(tr("Reject"),QMessageBox::ActionRole);

    msbox.exec();
    if(msbox.clickedButton() == accept)
    {
        QString temp = "accept";
        socket->write(temp.toStdString().c_str());
        socket->waitForBytesWritten(-1);
        msbox.close();
    }
    else if(msbox.clickedButton() == reject)
    {
        QString temp = "reject";
        socket->write(temp.toStdString().c_str());
        socket->waitForBytesWritten(-1);
        msbox.close();
    }
}

void client::slo_stop()
{
    QString temp = "Stop";
    socket->write(temp.toStdString().c_str());
    socket->waitForBytesWritten(-1);
}

void client::slo_resume()
{
    QString temp = "Resume";
    socket->write(temp.toStdString().c_str());
    socket->waitForBytesWritten(-1);
}

void client::slo_exit()
{
    QString temp = "Exit";
    socket->write(temp.toStdString().c_str());
    socket->waitForBytesWritten(-1);
}
