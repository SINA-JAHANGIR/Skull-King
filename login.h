#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QtMultimedia>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QMediaPlayer*,QWidget *parent = nullptr);
    ~login();

private slots:
    void on_btn_sign_in_clicked();
    void on_btn_sign_up_clicked();
    void on_btn_exit_clicked();

private:
    Ui::login *ui;
    QMediaPlayer* first_music;
};

#endif // LOGIN_H
