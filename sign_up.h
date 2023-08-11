#ifndef SIGN_UP_H
#define SIGN_UP_H

#include "person.h"
#include <QVector>
#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QRegularExpression>


namespace Ui {
class sign_up;
}

class sign_up : public QMainWindow
{
    Q_OBJECT

public:
    explicit sign_up(QWidget *parent = nullptr);
    ~sign_up();

private slots:
    void on_btn_save_clicked();
    void on_btn_cancel_clicked();
    void on_line_username_textChanged(const QString &);
    void on_line_password_textChanged(const QString &);
    void on_line_name_textChanged(const QString &);
    void on_line_phone_textChanged(const QString &);
    void on_line_email_textChanged(const QString &);

private:
    Ui::sign_up *ui;
    QWidget *par;
    bool username = false;
    bool password = false;
    bool name = false;
    bool phone = false;
    bool email = false;

    void change_label(QLabel*,QString,bool);
};

#endif // SIGN_UP_H
