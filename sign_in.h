#ifndef SIGN_IN_H
#define SIGN_IN_H

#include "person.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QtMultimedia>

enum with{password,phone};

namespace Ui {
class sign_in;
}

class sign_in : public QMainWindow
{
    Q_OBJECT

public:
    explicit sign_in(QMediaPlayer*,QWidget *parent = nullptr);
    ~sign_in();

private slots:
    void on_btn_log_in_clicked();    
    void on_btn_forgot_clicked();
    void on_btn_back_clicked();

private:
    Ui::sign_in *ui;
    with login_with = password;
    QWidget *par;
    QMediaPlayer* first_music;
};

#endif // SIGN_IN_H
