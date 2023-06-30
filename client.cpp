#include "client.h"
#include "ui_client.h"
#include "ui_game.h"
#include <windows.h>

#define BACK "QPushButton{border-image: url(:/photos/back-of-card.png);}"

client::client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    socket = new QTcpSocket;
    socket->connectToHost("127.0.0.1",1225);
    connect(socket,SIGNAL(connected()),this,SLOT(connected_to_server()));

    connect(socket,SIGNAL(readyRead()),this,SLOT(slo_read_card()));

    game_client_page = new game(this);
    connect(game_client_page,SIGNAL(sig_send_one_card(card)),this,SLOT(slo_send_one_card(card)));
    connect(game_client_page,SIGNAL(sig_change_card()),this,SLOT(slo_change_card()));
    thread = std::thread(&client::slo_read_card,this);
    spy = new QSignalSpy(this,SIGNAL(sig_continue()));
//    game_client_page->turn = p2;
    connect(this,SIGNAL(sig_game_continue()),&game_client_page->loop,SLOT(quit()));
    connect(game_client_page,SIGNAL(sig_send_forecast()),this,SLOT(slo_send_forecast()));
    connect(this,SIGNAL(sig_start()),this,SLOT(slo_call_dealer_animation()));
    connect(this,SIGNAL(sig_get_forecast()),&game_client_page->start,SLOT(quit()));
}

client::~client()
{
    thread.join();
    delete ui;
}

void client::connected_to_server()
{
    ui->btn_start->setEnabled(true);

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

void client::on_btn_start_clicked()
{
//    if(ready)
//    {

        this->hide();
        game_client_page->show();
        game_client_page->game_client_start();
        //    }
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
//                game_client_page->wait=false;
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
                socket->write(t.toStdString().c_str());
                socket->waitForBytesWritten(-1);
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
            else if(received == "ok")
            {
                emit sig_continue();
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
    spy->wait(1000);
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
