#include "customized_button.h"

customized_button::customized_button(QWidget *parent)
{
    if (button_number>0)
    {
        connect(this,SIGNAL(clicked(bool)),this,SLOT(slo_number_clicked()));
    }
    else
    {
        connect(this,SIGNAL(clicked(bool)),this,SLOT(slo_card_clicked()));
    }
}
void customized_button::slo_number_clicked()

{
    emit sig_number_clicked(button_number);
}

void customized_button::slo_card_clicked()
{
    emit sig_card_clicked(this);
}

customized_button::customized_button(int input)
{
    button_number = input;
    connect(this,SIGNAL(clicked(bool)),this,SLOT(slo_number_clicked()));
}

customized_button::customized_button(card input)
{
    button_card = input;
    button_number = -1;
    connect(this,SIGNAL(clicked(bool)),this,SLOT(slo_card_clicked()));
}

void customized_button::set_btn_number(int input)
{
    button_number = input;
}

int customized_button::get_btn_number()
{
    return button_number;
}

void customized_button::set_btn_card(card const input)
{
    button_card = input;
}

card customized_button::get_btn_card()
{
    return button_card;
}

void customized_button::change_obj_name()
{
    if (button_number>=0)
        this->setObjectName(QString::number(button_number));
    else
    {
        this->setObjectName(button_card.get_type_string()+QString::number(button_card.get_value()));
    }
}
