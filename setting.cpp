#include "setting.h"
#include "ui_setting.h"
#include "change.h"
#include <QScreen>
#include "login.h"

setting::setting(person per1,QMediaPlayer* fmusic,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setting)
{
    first_music = fmusic;
    ui->setupUi(this);
    p1 = per1;
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y - 30);
    par = parent;
}

setting::~setting()
{
    delete ui;
}

void setting::on_btn_back_clicked()
{
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    this->close();
    par->show();
}


void setting::on_btn_change_clicked()
{
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    par->hide();
    change* change_page = new change(p1,first_music,par);
    change_page->setWindowTitle("Skull King");
    this->close();
    change_page->show();
}


void setting::on_btn_log_out_clicked()
{
    QMediaPlayer* click = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(1);
    click->setAudioOutput(audioOutput);
    connect(click, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    click->setSource(QUrl("qrc:/sounds/click-button.mp3"));
    click->play();
    if (QFile::remove("gamer.txt"))
    {
        login* login_page = new login(first_music);
        this->close();
        login_page->show();
    }
    else
    {
        QMessageBox::warning(this,"ERROR !","The operation was not successful !");
        exit(13);
    }
}

