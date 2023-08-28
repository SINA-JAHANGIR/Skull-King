#ifndef CHANGE_H
#define CHANGE_H

#include "person.h"
#include <QVector>
#include <QMainWindow>
#include <QRegularExpression>
#include <QLabel>
#include <QMediaPlayer>

namespace Ui {
class change;
}

class change : public QMainWindow
{
    Q_OBJECT

public:
    explicit change(person,QMediaPlayer*,QWidget *parent = nullptr);
    ~change();

private slots:
    void on_btn_save_clicked();
    void on_btn_cancel_clicked();
    void on_line_username_textChanged(const QString &);
    void on_line_password_textChanged(const QString &);
    void on_line_name_textChanged(const QString &);
    void on_line_phone_textChanged(const QString &);
    void on_line_email_textChanged(const QString &);

private:
    Ui::change *ui;
    QWidget *par;
    person p1;
    QVector<person> people;
    bool username = false;
    bool password = false;
    bool name = false;
    bool phone = false;
    bool email = false;
    QMediaPlayer* first_music;
    void change_label(QLabel*,QString,bool);
};

#endif // CHANGE_H
