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
    if (username == false || password == false || name == false || phone == false || email == false)
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

void sign_up::change_label(QLabel* lbl,QString str,bool color)
{
    lbl->hide();
    if (color)
        lbl->setStyleSheet("QLabel {color: green;}");
    else
        lbl->setStyleSheet("QLabel {color: red;}");
    lbl->setText(str);
    lbl->show();
}

void sign_up::on_line_username_textChanged(const QString &text)
{
    QRegularExpression usernameRegex("^[a-zA-Z0-9\\-._]*$");
    if(text.isEmpty())
    {
        username = false;
        change_label(ui->lbl_username_massage,"Your username cannot be empty !",false);
    }
    else if (text.size() < 4)
    {
        username = false;
        change_label(ui->lbl_username_massage,"Your username must include at least 4-letters !",false);
    }
    else if (text.size() > 13)
    {
        username = false;
        change_label(ui->lbl_username_massage,"Your username must be 13 characters or less !",false);
    }
    else if ( text.contains(QChar(' ')))
    {
        username = false;
        change_label(ui->lbl_username_massage,"Your username must not include space !",false);
    }
    else if (usernameRegex.match(text).hasMatch())
    {
        username = true;
        change_label(ui->lbl_username_massage,"Your username is valid .",true);
    }
    else
    {
        username = false;
        change_label(ui->lbl_username_massage,"Your username is invalid .",false);
    }
}


void sign_up::on_line_password_textChanged(const QString &text)
{
    QRegularExpression upperCaseRegex("[A-Z]");
    QRegularExpression lowerCaseRegex("[a-z]");
    QRegularExpression numberRegex("[0-9]");
    QRegularExpression passRegex("^[a-zA-Z0-9\\-._]*$");
    if(text.isEmpty())
    {
        password = false;
        change_label(ui->lbl_password_massage,"Your password cannot be empty !",false);
    }
    else if (text.size() < 8)
    {
        password = false;
        change_label(ui->lbl_password_massage,"Your password must include at least 8-letters !",false);
    }
    else if ( text.contains(QChar(' ')))
    {
        password = false;
        change_label(ui->lbl_password_massage,"Your password must not include space !",false);
    }
    else if (!text.contains(upperCaseRegex))
    {
        password = false;
        change_label(ui->lbl_password_massage,"Your password must include uppercase characters !",false);
    }
    else if (!text.contains(lowerCaseRegex))
    {
        password = false;
        change_label(ui->lbl_password_massage,"Your password must include lowercase characters !",false);
    }
    else if (!text.contains(numberRegex))
    {
        password = false;
        change_label(ui->lbl_password_massage,"Your password must include number !",false);
    }
    else if (!text.contains(QChar('.')) && !text.contains(QChar('-')) && !text.contains(QChar('_')))
    {
        password = false;
        change_label(ui->lbl_password_massage,"Your password must include dash,dot or underscore !",false);
    }
    else if (passRegex.match(text).hasMatch())
    {
        password = true;
        change_label(ui->lbl_password_massage,"Your password is valid .",true);
    }
    else
    {
        password = false;
        change_label(ui->lbl_password_massage,"Your password is invalid .",false);
    }
}


void sign_up::on_line_name_textChanged(const QString &text)
{
    QRegularExpression lettersOnlyRegex("^[a-zA-Z]*$");
    if(text.isEmpty())
    {
        name = false;
        change_label(ui->lbl_name_massage,"Your name cannot be empty !",false);
    }
    else if ( text.contains(QChar(' ')))
    {
        name = false;
        change_label(ui->lbl_name_massage,"Your name must not include space !",false);
    }
    else if (lettersOnlyRegex.match(text).hasMatch())
    {
        name = true;
        change_label(ui->lbl_name_massage,"Your name is valid .",true);
    }
    else
    {
        name = false;
        change_label(ui->lbl_name_massage,"Your name is invalid .",false);
    }
}


void sign_up::on_line_phone_textChanged(const QString &text)
{
    QRegularExpression numberRegex("^[0-9]*$");
    if(text.isEmpty())
    {
        phone = false;
        change_label(ui->lbl_phone_massage,"Your phone number cannot be empty !",false);
    }
    else if ( text.contains(QChar(' ')))
    {
        phone = false;
        change_label(ui->lbl_phone_massage,"Your phone number must not include space !",false);
    }
    else if (text.size() < 11)
    {
        phone = false;
        change_label(ui->lbl_phone_massage,"Your phone number must include at least 11-letters !",false);
    }
    else if (text.size() > 13)
    {
        phone = false;
        change_label(ui->lbl_phone_massage,"Your phone must be 13 characters or less !",false);
    }
    else if (numberRegex.match(text).hasMatch())
    {
        phone = true;
        change_label(ui->lbl_phone_massage,"Your phone is valid .",true);
    }
    else
    {
        phone = false;
        change_label(ui->lbl_phone_massage,"Your phone is invalid !",false);
    }
}


void sign_up::on_line_email_textChanged(const QString &text)
{
    QRegularExpression emailRegex(R"(^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{3,}))$)");
    if(text.isEmpty())
    {
        email = false;
        change_label(ui->lbl_email_massage,"Your email cannot be empty !",false);
    }
    else if ( text.contains(QChar(' ')))
    {
        email = false;
        change_label(ui->lbl_email_massage,"Your email must not include space !",false);
    }
    else if (emailRegex.match(text).hasMatch())
    {
        email = true;
        change_label(ui->lbl_email_massage,"Your email is valid .",true);
    }
    else
    {
        email = false;
        change_label(ui->lbl_email_massage,"Your email is invalid !",false);
    }
}

