#include "change.h"
#include "ui_change.h"
#include "mainwindow.h"
#include <QScreen>

change::change(person per1,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::change)
{
    ui->setupUi(this);
    p1 = per1;
    par = parent;
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
    ui->line_username->setText(p1.get_username());
    ui->line_password->setText(p1.get_password());
    ui->line_name->setText(p1.get_name());
    ui->line_phone->setText(p1.get_phone());
    ui->line_email->setText(p1.get_email());
}

change::~change()
{
    delete ui;
}

void change::on_btn_save_clicked()
{
    QFile file("account.txt");
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
                temp;
            if (username == p1.get_username())
            {
                continue;
            }
            if (username == "" || password == "" || name == "" || phone == "" || email == "")
            {
                break;
            }
            person temp ;
            temp.set_username(username);
            temp.set_password(password);
            temp.set_name(name);
            temp.set_phone(phone);
            temp.set_email(email);
            temp.set_coin(coin);
            people.append(temp);
        }
    }
    file.close();
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"ERROR !","The operation was not successful !");
        exit(13);
    }
    else
    {
        QTextStream out(&file);
        for (int i = 0 ; i < people.size() ; i++)
        {
            out << people[i].get_username() << '\n'
                << people[i].get_password() << '\n'
                << people[i].get_name() << '\n'
                << people[i].get_phone() << '\n'
                << people[i].get_email() << '\n'
                << people[i].get_coin() << '\n'
                << "----------------------------------------------------" << '\n';
        }
    }
    file.close();
    people.clear();
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
                temp;
            if (username == ui->line_username->text())
            {
                QMessageBox::warning(this,"ERROR !","This username has been registered !");
                return;
            }
        }
    }
    file.close();
    p1.set_username(ui->line_username->text());
    p1.set_password(ui->line_password->text());
    p1.set_name(ui->line_name->text());
    p1.set_phone(ui->line_phone->text());
    p1.set_email(ui->line_email->text());
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
    par->close();
    MainWindow* main_page = new MainWindow(p1);
    main_page->setWindowTitle("Skull King");
    this->close();
    main_page->show();
}


void change::on_btn_cancel_clicked()
{
    this->close();
    par->show();
}

