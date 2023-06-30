#include "change.h"
#include "ui_change.h"
#include "mainwindow.h"
#include <QScreen>

change::change(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::change)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
}

change::~change()
{
    delete ui;
}

void change::on_btn_save_clicked()
{
    MainWindow* main_page = new MainWindow;
    main_page->setWindowTitle("Skull King");
    this->close();
    main_page->show();
}

