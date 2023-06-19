#include "customized_button.h"

customized_button::customized_button(QWidget *parent)
{
    connect(this,SIGNAL(clicked(bool)),this,SLOT(slo_handle_click()));
}
void customized_button::slo_handle_click()
{
    emit sig_button_clicked(button_number);
}
