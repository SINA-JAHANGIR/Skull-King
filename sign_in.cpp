#include "sign_in.h"
#include "ui_sign_in.h"
#include <QScreen>
#include "mainwindow.h"


sign_in::sign_in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sign_in)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
}

sign_in::~sign_in()
{
    delete ui;
}

void sign_in::on_btn_log_in_clicked()
{
    MainWindow* main_page = new MainWindow;
    main_page->setWindowTitle("Skull King");
    this->close();
    main_page->show();
}

