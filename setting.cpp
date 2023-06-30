#include "setting.h"
#include "ui_setting.h"
#include "change.h"
#include <QScreen>

setting::setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
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
    change* change_page = new change;
    change_page->setWindowTitle("Skull King");
    this->close();
    change_page->show();
}

