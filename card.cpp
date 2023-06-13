#include "card.h"

card::card(QWidget *parent)
    : QWidget{parent}
{
    value = 0 ;
    selected = false;
}

void card::set_type(const card_type& input)
{
    this->type = input;
}

const card_type card::get_type()
{
    return type;
}

void card::set_value(const int& input)
{
    this->value = input;
}

const int card::get_value()
{
    return value;
}

void card::set_selected(const bool& input)
{
    this->selected = input;
}

const bool card::get_selected()
{
    return selected;
}
