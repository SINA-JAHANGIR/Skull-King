#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_btn_sign_in_clicked();

    void on_btn_sign_up_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H