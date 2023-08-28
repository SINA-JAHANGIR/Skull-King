#ifndef HISTORY_H
#define HISTORY_H

#include <QMainWindow>
#include "person.h"
#include <QLabel>
#include <QVector>
#include <QPushButton>
#include <QMediaPlayer>
#include <QtMultimedia>

namespace Ui {
class history;
}

class history : public QMainWindow
{
    Q_OBJECT

public:
    explicit history(person,QWidget *parent = nullptr);
    ~history();

private slots:
    void on_btn_back_clicked();

private:
    Ui::history *ui;
    QWidget *par;
    person person1;
    QString change_card_stylesheet(int);
    void change_lbl_stylesheet(QLabel*,QString);
    QVector<QPushButton*> cards;
};

#endif // HISTORY_H
