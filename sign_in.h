#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QMainWindow>

namespace Ui {
class sign_in;
}

class sign_in : public QMainWindow
{
    Q_OBJECT

public:
    explicit sign_in(QWidget *parent = nullptr);
    ~sign_in();

private slots:
    void on_btn_log_in_clicked();

private:
    Ui::sign_in *ui;
};

#endif // SIGN_IN_H
