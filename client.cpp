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
}

client::~client()
{
    delete ui;
}

void client::connected_to_server()
{


}
