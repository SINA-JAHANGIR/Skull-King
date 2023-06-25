#include "client.h"
#include "ui_client.h"

client::client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    socket = new QTcpSocket;
    socket->connectToHost("127.0.0.1",1225);
    connect(socket,SIGNAL(connected()),this,SLOT(connected_to_server()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(slo_read_card()));
}

client::~client()
{
    delete ui;
}

void client::connected_to_server()
{
    game_client_page = new game(this);
    this->close();
    game_client_page->show();
}


QByteArray client::card_to_qbytearray(const card& input){
    QByteArray output;
    QDataStream stream(&output, QIODevice::ReadWrite);
    stream <<input.get_type()<<input.get_value()<<input.get_selected();

    return output;
}
card client::qbytearray_to_card(QByteArray& input)
{
    card output;
    QDataStream stream(&input, QIODevice::ReadWrite);

    card_type type;
    int value;
    bool selected;
    stream >>type>>value>>selected;

    output.set_type(type);
    output.set_value(value);
    output.set_selected(selected);

    return output;
}

void client::on_btn_start_clicked()
{
//    if(ready)
//    {
//        game_client_page = new game(this);
//        this->close();
//        game_client_page->show();
//    }
}

void client::slo_read_card()
{

    QByteArray card_byte = socket->readAll();
    card temp = qbytearray_to_card(card_byte);
    if(temp.get_selected()==true)
    {
        //
    }
    else{
        customized_button *new_button = new customized_button(temp);
        game_client_page->player1.cards.append(new_button);
    }
    socket->write("1");
}
