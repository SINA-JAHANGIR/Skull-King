#include "sign_up.h"
#include "ui_sign_up.h"
#include <QScreen>
#include "mainwindow.h"
sign_up::sign_up(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sign_up)
{
    ui->setupUi(this);
    par = parent;
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
    if (ui->line_username->text() == ""
        || ui->line_password->text() == ""
        || ui->line_name->text() == ""
        || ui->line_phone->text() == ""
        || ui->line_email->text() == "" )
    {
        QMessageBox::warning(this,"ERROR !","Please fill out the form completely !");
        return;
    }
    QFile file("account.txt");
    if(file.exists())
    {
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"ERROR !","The operation was not successful !");
            exit(13);
        }
        else
        {
            QTextStream in(&file);
            QString username , password , name , phone , email , temp;
            int coin;
            while(!in.atEnd())
            {
                in >> username >>
                    password >>
                    name >>
                    phone >>
                    email >>
                    coin >>
                    temp ;
                if (username == ui->line_username->text())
                {
                    QMessageBox::warning(this,"ERROR !","This username has been registered !");
                    return;
                }
            }
        }
    }
    file.close();
    person p1;
    p1.set_username(ui->line_username->text());
    p1.set_password(ui->line_password->text());
    p1.set_name(ui->line_name->text());
    p1.set_phone(ui->line_phone->text());
    p1.set_email(ui->line_email->text());
    p1.set_coin(1000);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QMessageBox::warning(this,"ERROR !","The operation was not successful !");
        exit(13);
    }
    else
    {
        QTextStream out(&file);
        out << p1.get_username() << '\n'
            << p1.get_password() << '\n'
            << p1.get_name() << '\n'
            << p1.get_phone() << '\n'
            << p1.get_email() << '\n'
            << p1.get_coin() << '\n'
            << "----------------------------------------------------" << '\n';
    }
    file.close();
    QFile gamer_file("gamer.txt");
    if(!gamer_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"ERROR !","The operation was not successful !");
        exit(13);
    }
    else
    {
        QTextStream outg(&gamer_file);
        outg << p1.get_username() << '\n' <<
            p1.get_password() << '\n' <<
            p1.get_name() << '\n' <<
            p1.get_phone() << '\n' <<
            p1.get_email() << '\n' <<
            p1.get_coin() ;
    }
    gamer_file.close();
    MainWindow* main_page = new MainWindow(p1);
    main_page->setWindowTitle("Skull King");
    this->close();
    main_page->show();
}


void sign_up::on_btn_cancel_clicked()
{
    this->close();
    par->show();
}

