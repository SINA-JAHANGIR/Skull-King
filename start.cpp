#include "start.h"
#include "ui_start.h"

start::start(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
}

start::~start()
{
    delete ui;
}

void start::on_btn_host_clicked()
{
    host = new server(this);
    this->hide();
    host->show();
}


void start::on_btn_join_clicked()
{
    join = new client(this);
    this->hide();
    join->show();
}

