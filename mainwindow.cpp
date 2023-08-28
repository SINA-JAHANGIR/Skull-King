#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include "setting.h"
#include "history.h"

MainWindow::MainWindow(person per1,QMediaPlayer* fmusic,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p1 = per1;
    first_music = fmusic;
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
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    start_page = new start(p1,first_music,this);
    this->hide();
    start_page->setWindowTitle("Skull King");
    start_page->show();
}

void MainWindow::on_btn_setting_clicked()
{
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    setting* setting_page = new setting(p1,first_music,this);
    setting_page->setWindowTitle("Skull King");
    this->hide();
    setting_page->show();
}

void MainWindow::on_btn_history_clicked()
{
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    history* history_page = new history(p1,this);
    history_page->setWindowTitle("Skull King");
    this->hide();
    history_page->show();
}


void MainWindow::on_btn_exit_clicked()
{
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    this->close();
    exit(13);
}





