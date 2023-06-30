#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include "setting.h"
#include "history.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_play_clicked()
{
    start_page = new start(this);
    this->hide();
    start_page->setWindowTitle("Skull King");
    start_page->show();
}

void MainWindow::on_btn_setting_clicked()
{
    setting* setting_page = new setting(this);
    setting_page->setWindowTitle("Skull King");
    this->hide();
    setting_page->show();
}

void MainWindow::on_btn_history_clicked()
{
    history* history_page = new history(this);
    history_page->setWindowTitle("Skull King");
    this->hide();
    history_page->show();
}


void MainWindow::on_btn_exit_clicked()
{
    this->close();
    exit(13);
}





