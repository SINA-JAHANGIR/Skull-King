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
    game_server_page = new game(this);
    connect(game_server_page,SIGNAL(sig_send_card()),this,SLOT(slo_send_card()));
    connect(game_server_page,SIGNAL(sig_send_one_card(card)),this,SLOT(slo_send_one_card(card)));
}

server::~server()
{
    thread.join();
    delete ui;
}

void server::connection_new(){
    client_socket = game_server->nextPendingConnection();
    this->ui->btn_start->setEnabled(true);
    thread = std::thread(&server::slo_read_card,this);
    spy = new QSignalSpy(this,SIGNAL(sig_continue()));
//    connect(client_socket,SIGNAL(readyRead()),this,SLOT(slo_read_card()));
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
    QString t = "player1";
    for( int i=0 ; i < game_server_page->player2.cards.size() ; i++ )
    {
        client_socket->write(t.toStdString().c_str());
        client_socket->waitForBytesWritten(-1);
        spy->wait(1000);
        QByteArray temp2 = client_socket->readAll();
        customized_button* temp = game_server_page->player2.cards[i];
        QByteArray card_byte = card_to_qbytearray(temp->get_btn_card());
        client_socket->write(card_byte);
        client_socket->waitForBytesWritten(-1);
        spy->wait(1000);
        temp2 = client_socket->readAll();
    }
    t = "player2";
    for( int i=0 ; i < game_server_page->player1.cards.size() ; i++ )
    {
        client_socket->write(t.toStdString().c_str());
        client_socket->waitForBytesWritten(-1);
        spy->wait(1000);
        QByteArray temp2 = client_socket->readAll();
        customized_button* temp = game_server_page->player1.cards[i];
        QByteArray card_byte = card_to_qbytearray(temp->get_btn_card());
        client_socket->write(card_byte);
        client_socket->waitForBytesWritten(-1);
        spy->wait(1000);
        temp2 = client_socket->readAll();
    }
    t="end";
    client_socket->write(t.toStdString().c_str());
    spy->wait(1000);
    QByteArray temp2 = client_socket->readAll();
    game_server_page->fl = false;
}

void server::slo_send_one_card(card input)
{
    QString t ="selected";
    client_socket->write(t.toStdString().c_str());
    client_socket->waitForBytesWritten(-1);
    spy->wait(1000);
    QByteArray temp2 = client_socket->readAll();
    QByteArray card_byte = card_to_qbytearray(input);
    client_socket->write(card_byte);
    client_socket->waitForBytesWritten(-1);
    spy->wait(1000);
    temp2 = client_socket->readAll();
}

void server::slo_read_card()
{
    while(true)
    {
        if(client_socket->waitForReadyRead(-1))
        {
            QByteArray received = client_socket->readAll();
            if(received == "ok")
            {
                emit sig_continue();
                received.clear();
            }
            else
            {
                card temp = qbytearray_to_card(received);
                //...
            }
        }
    }
}
