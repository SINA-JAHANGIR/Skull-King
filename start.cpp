#include "start.h"
#include "ui_start.h"
#include <QScreen>

start::start(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    par = parent;
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
}

start::~start()
{
    delete ui;
}

void start::on_btn_host_clicked()
{
    host = new server(par);
    this->hide();
    host->setWindowTitle("Skull King");
    host->show();
}


void start::on_btn_join_clicked()
{
    join = new client(par);
    this->hide();
    join->setWindowTitle("Skull King");
    join->show();
}

