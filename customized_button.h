#ifndef CUSTOMIZED_BUTTON_H
#define CUSTOMIZED_BUTTON_H

#include <QPushButton>
#include <QObject>

class customized_button : public QPushButton
{
    Q_OBJECT
public:
    customized_button(QWidget *parent = 0);
    int button_number;
signals:
    void sig_button_clicked(int);
private slots:
    void slo_handle_click();
};

#endif // CUSTOMIZED_BUTTON_H
