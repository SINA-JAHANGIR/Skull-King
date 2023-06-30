#ifndef CHANGE_H
#define CHANGE_H

#include <QMainWindow>

namespace Ui {
class change;
}

class change : public QMainWindow
{
    Q_OBJECT

public:
    explicit change(QWidget *parent = nullptr);
    ~change();

private slots:
    void on_btn_save_clicked();

private:
    Ui::change *ui;
};

#endif // CHANGE_H
