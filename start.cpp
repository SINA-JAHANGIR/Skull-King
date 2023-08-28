#include "start.h"
#include "ui_start.h"
#include <QScreen>

start::start(person per1,QMediaPlayer* fmusic,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::start)
{
    first_music = fmusic;
    ui->setupUi(this);
    p1 = per1;
    par = parent;
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
}

start::~start()
{
    delete ui;
}

void start::on_btn_host_clicked()
{
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    host = new server(p1,first_music,par);
    this->close();
    host->setWindowTitle("Skull King");
    host->show();
}


void start::on_btn_join_clicked()
{
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    join = new client(p1,first_music,par);
    this->close();
    join->setWindowTitle("Skull King");
    join->show();
}

