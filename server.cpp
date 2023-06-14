#include "server.h"
#include "ui_server.h"

server::server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    game_server = new QTcpServer();
    game_server->listen(QHostAddress::Any,1225);
    connect(game_server,SIGNAL(newConnection()),this,SLOT(connection_new()));
}

server::~server()
{
    delete ui;
}

void server::connection_new(){
    client_socket = game_server->nextPendingConnection();
}

QByteArray server::card_to_qbytearray(const card& input){
    QByteArray output;
    QDataStream stream(&output, QIODevice::ReadWrite);
    stream <<input.get_type()<<input.get_value()<<input.get_selected();

    return output;
}
card server::qbytearray_to_card(QByteArray& input)
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
