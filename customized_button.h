#ifndef CUSTOMIZED_BUTTON_H
#define CUSTOMIZED_BUTTON_H

#include <QPushButton>
#include <QObject>
#include "card.h"

class customized_button : public QPushButton
{
    Q_OBJECT
private:
    int button_number;
    card button_card;
public:
    customized_button(int);
    customized_button(card);
    customized_button(QWidget *parent = 0);
    void set_btn_number(int);
    int get_btn_number();
    void set_btn_card(card);
    card get_btn_card();
    void change_obj_name();
signals:
    void sig_number_clicked(int);
    void sig_card_clicked(customized_button*);
private slots:
    void slo_number_clicked();
    void slo_card_clicked();
};

#endif // CUSTOMIZED_BUTTON_H
