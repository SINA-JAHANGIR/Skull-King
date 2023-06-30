#include "login.h"
#include "ui_login.h"
#include <QScreen>
#include "sign_in.h"
#include "sign_up.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
}

login::~login()
{
    delete ui;
}

void login::on_btn_sign_in_clicked()
{
    sign_in* in_page = new sign_in;
    in_page->setWindowTitle("Skull King");
    this->close();
    in_page->show();
}


void login::on_btn_sign_up_clicked()
{
    sign_up* up_page = new sign_up;
    up_page->setWindowTitle("Skull King");
    this->close();
    up_page->show();
}

