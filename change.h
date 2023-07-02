#ifndef CHANGE_H
#define CHANGE_H

#include "person.h"
#include <QVector>
#include <QMainWindow>

namespace Ui {
class change;
}

class change : public QMainWindow
{
    Q_OBJECT

public:
    explicit change(person,QWidget *parent = nullptr);
    ~change();

private slots:
    void on_btn_save_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::change *ui;
    QWidget *par;
    person p1;
    QVector<person> people;
};

#endif // CHANGE_H
