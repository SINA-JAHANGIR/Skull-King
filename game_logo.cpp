#include "game_logo.h"
#include "ui_game_logo.h"
#include <QScreen>
#include <windows.h>
#include "mainwindow.h"
#include "login.h"
#include <iostream>
#include <fstream>
using namespace std;

game_logo::game_logo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game_logo)
{
    first_music = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    first_music->setAudioOutput(audioOutput);
    connect(first_music, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    first_music->setSource(QUrl("qrc:/sounds/Taylor Davis - He's a Pirate (320).mp3"));
    audioOutput->setVolume(100);
    first_music->setPosition(500);
    first_music->setLoops(3);
    first_music->play();
    Sleep(2000);

    ui->setupUi(this);
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
    lbl_logo = new QLabel(this);
    lbl_logo->setParent(ui->centralwidget);
    QPixmap pixmap(":/photos/game logo.png");
    lbl_logo->setPixmap(pixmap);
    lbl_logo->raise();
    lbl_logo->show();
    animation = new QPropertyAnimation(lbl_logo,"geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(width()/2-325,0,650,375));
    animation->setEndValue(QRect(width()/2-325,height()/2-400,1300,750));
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(slo_next_page()));
}

game_logo::~game_logo()
{
    delete ui;
}

void game_logo::slo_next_page()
{
    person p1;
    QFile gamer_file("gamer.txt");
    if(gamer_file.exists())
    {
        if(!gamer_file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"ERROR !","The operation was not successful !");
            exit(13);
        }
        else
        {
            QTextStream in(&gamer_file);
            QString username , password , name , phone , email , temp;
            int coin;
            in >> username >>
                password >>
                name >>
                phone >>
                email >>
                coin ;
            p1.set_username(username);
            p1.set_password(password);
            p1.set_name(name);
            p1.set_phone(phone);
            p1.set_email(email);
            p1.set_coin(coin);
        }
        MainWindow* main_page = new MainWindow(p1,first_music);
        main_page->setWindowTitle("Skull King");
        this->hide();
        main_page->show();
        return;
    }
    else
    {
        gamer_file.close();
        login* login_page = new login(first_music);
        login_page->setWindowTitle("Skull King");
        this->hide();
        login_page->show();
    }
}
