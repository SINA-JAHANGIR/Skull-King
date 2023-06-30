#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QMainWindow>

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

private:
    Ui::sign_up *ui;
};

#endif // SIGN_UP_H
