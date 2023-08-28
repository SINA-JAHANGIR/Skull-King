#include "login.h"
#include "ui_login.h"
#include <QScreen>
#include "sign_in.h"
#include "sign_up.h"

login::login(QMediaPlayer* fmusic,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    first_music = fmusic;
    ui->setupUi(this);
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
}

login::~login()
{
    delete ui;
}

void login::on_btn_sign_in_clicked()
{
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    sign_in* in_page = new sign_in(first_music,this);
    in_page->setWindowTitle("Skull King");
    this->close();
    in_page->show();
}


void login::on_btn_sign_up_clicked()
{
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    sign_up* up_page = new sign_up(first_music,this);
    up_page->setWindowTitle("Skull King");
    this->close();
    up_page->show();
}


void login::on_btn_exit_clicked()
{
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    exit(13);
}

