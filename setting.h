#ifndef SETTING_H
#define SETTING_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include "person.h"

namespace Ui {
class setting;
}

class setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit setting(person,QWidget *parent = nullptr);
    ~setting();

private slots:
    void on_btn_back_clicked();
    void on_btn_change_clicked();

    void on_btn_log_out_clicked();

private:
    Ui::setting *ui;
    QWidget *par;
    person p1;
};

#endif // SETTING_H
