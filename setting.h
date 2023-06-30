#ifndef SETTING_H
#define SETTING_H

#include <QMainWindow>

namespace Ui {
class setting;
}

class setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();

private slots:
    void on_btn_back_clicked();
    void on_btn_change_clicked();

private:
    Ui::setting *ui;
    QWidget *par;
};

#endif // SETTING_H
