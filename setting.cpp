#include "setting.h"
#include "ui_setting.h"
#include "change.h"
#include <QScreen>
#include "login.h"

setting::setting(person per1,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    p1 = per1;
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
    par = parent;
}

setting::~setting()
{
    delete ui;
}

void setting::on_btn_back_clicked()
{
    this->close();
    par->show();
}


void setting::on_btn_change_clicked()
{
    par->hide();
    change* change_page = new change(p1,par);
    change_page->setWindowTitle("Skull King");
    this->close();
    change_page->show();
}


void setting::on_btn_log_out_clicked()
{
    if (QFile::remove("gamer.txt"))
    {
        login* login_page = new login;
        this->close();
        login_page->show();
    }
    else
    {
        QMessageBox::warning(this,"ERROR !","The operation was not successful !");
        exit(13);
    }
}

