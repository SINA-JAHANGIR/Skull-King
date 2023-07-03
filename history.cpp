#include "history.h"
#include "ui_history.h"
#include <QScreen>
#include <QFile>
#include <QMessageBox>
#include <QRect>

history::history(person per1,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
    par = parent;
    person1 = per1;
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
    int coin = person1.get_coin() , win_number = 0 , lose_number = 0 , draw_number = 0 ;
    QString username = "----------" , p2_username_1 = "----------", p2_username_2 = "----------", p2_username_3 = "----------",
        win_lose1 = "-----", win_lose2 = "-----" , win_lose3 = "-----";
    int p1_card_1 = 100 , p1_card_2 = 100 , p1_card_3 = 100 , p2_card_1 = 100 , p2_card_2 = 100 , p2_card_3 = 100 ;
    QFile history_file(person1.get_username()+".txt");
    if(history_file.exists())
    {
        if(!history_file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"ERROR !","The operation was not successful !");
            exit(13);
        }
        else
        {
            QTextStream in(&history_file);
            in >> coin >>
                username >>
                win_number >>
                lose_number >>
                draw_number >>
                p2_username_1 >>
                win_lose1 >>
                p1_card_1 >>
                p2_card_1
                >> p2_username_2 >>
                win_lose2 >>
                p1_card_2 >>
                p2_card_2
                >>p2_username_3 >>
                win_lose3 >>
                p1_card_3 >>
                p2_card_3 ;
        }
        history_file.close();
    }
    ui->lbl_p1_username->setText(person1.get_username());
    ui->lbl_coin_number->setText(QString::number(coin));
    ui->lbl_win_number->setText(QString::number(win_number));
    ui->lbl_lose_number->setText(QString::number(lose_number));
    ui->lbl_draw_number->setText(QString::number(draw_number));
    ui->lbl_p2_username_1->setText(p2_username_1);
    ui->lbl_p2_username_2->setText(p2_username_2);
    ui->lbl_p2_username_3->setText(p2_username_3);
    ui->lbl_p1_win_lose_1->setText(win_lose1);
    change_lbl_stylesheet( ui->lbl_p1_win_lose_1,win_lose1);
    ui->lbl_p1_win_lose_2->setText(win_lose2);
    change_lbl_stylesheet( ui->lbl_p1_win_lose_2,win_lose2);
    ui->lbl_p1_win_lose_3->setText(win_lose3);
    change_lbl_stylesheet( ui->lbl_p1_win_lose_3,win_lose3);
    QString temp;

    QPushButton* btn_p1_1 = new QPushButton;
    btn_p1_1->setParent(this);
    btn_p1_1->setGeometry(QRect(850,360,71,101));
    temp = change_card_stylesheet(p1_card_1);
    btn_p1_1->setStyleSheet(temp);
    btn_p1_1->show();

    QPushButton* btn_p1_2 = new QPushButton;
    btn_p1_2->setParent(this);
    btn_p1_2->setGeometry(QRect(850,460,71,101));
    temp = change_card_stylesheet(p1_card_2);
    btn_p1_2->setStyleSheet(temp);
    btn_p1_2->show();

    QPushButton* btn_p1_3 = new QPushButton;
    btn_p1_3->setParent(this);
    btn_p1_3->setGeometry(QRect(850,560,71,101));
    temp = change_card_stylesheet(p1_card_3);
    btn_p1_3->setStyleSheet(temp);
    btn_p1_3->show();

    QPushButton* btn_p2_1 = new QPushButton;
    btn_p2_1->setParent(this);
    btn_p2_1->setGeometry(QRect(1100,360,71,101));
    temp = change_card_stylesheet(p2_card_1);
    btn_p2_1->setStyleSheet(temp);
    btn_p2_1->show();

    QPushButton* btn_p2_2 = new QPushButton;
    btn_p2_2->setParent(this);
    btn_p2_2->setGeometry(QRect(1100,460,71,101));
    temp = change_card_stylesheet(p2_card_2);
    btn_p2_2->setStyleSheet(temp);
    btn_p2_2->show();

    QPushButton* btn_p2_3 = new QPushButton;
    btn_p2_3->setParent(this);
    btn_p2_3->setGeometry(QRect(1100,560,71,101));
    temp = change_card_stylesheet(p2_card_3);
    btn_p2_3->setStyleSheet(temp);
    btn_p2_3->show();
}

history::~history()
{
    delete ui;
}

void history::on_btn_back_clicked()
{
    this->close();
    par->show();
}

QString history::change_card_stylesheet(int n)
{
    QString temp;
    switch(n)
    {
    case 0 : case 1 : case 2 : case 3 : case 4 : case 5 : case 6 : case 7 : case 8 : case 9 : case 10 :
        temp = "QPushButton{border-image: url(:/photos/parrot " + QString::number(n+1) + ".png);}";
        break;
    case 11 : case 12 : case 13 : case 14 : case 15 : case 16 : case 17 : case 18 : case 19 : case 20 : case 21 :
        temp = "QPushButton{border-image: url(:/photos/gold " + QString::number(n-10) + ".png);}";
        break;
    case 22 : case 23 : case 24 : case 25 : case 26 : case 27 : case 28 : case 29 : case 30 : case 31 : case 32 :
        temp = "QPushButton{border-image: url(:/photos/map " + QString::number(n-21) + ".png);}";
        break;
    case 33 : case 34 : case 35 : case 36 : case 37 : case 38 : case 39 : case 40 : case 41 : case 42 : case 43 :
        temp = "QPushButton{border-image: url(:/photos/flag " + QString::number(n-32) + ".png);}";
        break;
    case 44 : case 45 : case 46 : case 47 :
        temp = "QPushButton{border-image: url(:/photos/pirate " + QString::number(n-43) + ".png);}";
        break;
    case 48 : case 49 : case 50 : case 51 :
        temp = "QPushButton{border-image: url(:/photos/queen " + QString::number(n-47) + ".png);}";
        break;
    case 52 : case 53 : case 54 : case 55 :
        temp = "QPushButton{border-image: url(:/photos/king " + QString::number(n-51) + ".png);}";
        break;
    default:
        temp = "QPushButton{border-image: url(:/photos/skull-king-pirate.png);}";
    }
    return temp;
}

void history::change_lbl_stylesheet(QLabel* lbl,QString input)
{
    QString temp;
    if (input == "Win" )
    {
        temp = "QLabel {color: green;}";
    }
    else if (input == "Lose")
    {
        temp = "QLabel {color: red;}";
    }
    else if (input == "Draw")
    {
        temp = "QLabel {color: yellow;}";
    }
    lbl->setStyleSheet(temp);
}

