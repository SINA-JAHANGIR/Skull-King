#include "sign_up.h"
#include "ui_sign_up.h"
#include <QScreen>
#include "mainwindow.h"
sign_up::sign_up(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sign_up)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
}

sign_up::~sign_up()
{
    delete ui;
}


void sign_up::on_btn_save_clicked()
{
    MainWindow* main_page = new MainWindow;
    main_page->setWindowTitle("Skull King");
    this->close();
    main_page->show();
}

