#include "sign_in.h"
#include "ui_sign_in.h"
#include <QScreen>
#include "mainwindow.h"


sign_in::sign_in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sign_in)
{
    ui->setupUi(this);
    par = parent;
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
    person p1;
    bool flag = true;
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
                    if (login_with == with::password)
                    {
                        if (password == ui->line_password->text())
                        {
                            p1.set_username(username);
                            p1.set_password(password);
                            p1.set_name(name);
                            p1.set_phone(phone);
                            p1.set_email(email);
                            p1.set_coin(coin);
                            flag = false;
                            break;
                        }
                        else
                        {
                            QMessageBox::warning(this,"ERROR !","Incorrect password !");
                            return;
                        }
                    }
                    else
                    {
                        if (phone == ui->line_password->text())
                        {
                            p1.set_username(username);
                            p1.set_password(password);
                            p1.set_name(name);
                            p1.set_phone(phone);
                            p1.set_email(email);
                            p1.set_coin(coin);
                            flag = false;
                            break;
                        }
                        else
                        {
                            QMessageBox::warning(this,"ERROR !","Incorrect phone number !");
                            return;
                        }
                    }
                }
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"ERROR !","Not found !");
        return;
    }
    if (flag)
    {
        QMessageBox::warning(this,"ERROR !","Not found !");
        return;
    }
    file.close();
    QFile gamer_file("gamer.txt");
    if(!gamer_file.open(QIODevice::WriteOnly | QIODevice::Append))
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


void sign_in::on_btn_forgot_clicked()
{
    if (login_with == password)
    {
        ui->lbl_password->hide();
        ui->lbl_password->setText("Phone : ");
        ui->lbl_password->show();
        ui->btn_forgot->setText("Login with password");
        QMessageBox::information(this,"Forgot your password?","Login with username and phone number .");
        login_with = phone;
    }
    else
    {
        ui->lbl_password->hide();
        ui->lbl_password->setText("Password :");
        ui->lbl_password->show();
        ui->btn_forgot->setText("Forgot password ?");
        QMessageBox::information(this,"Forgot your phone number ?","Login with username and password .");
        login_with = password;
    }
}


void sign_in::on_btn_back_clicked()
{
    this->close();
    par->show();
}

