#include "card.h"

card::card(QWidget *parent)
    : QWidget{parent}
{
    value = 0 ;
    selected = false;
}

card::card(const card& input)
{
    this->set_type(input.get_type());
    this->set_value(input.get_value());
    this->set_selected(input.get_selected());
}

card card::operator=(const card& input)
{
    this->set_type(input.get_type());
    this->set_value(input.get_value());
    this->set_selected(input.get_selected());
    return *this;
}

void card::set_type(const card_type& input)
{
    this->type = input;
}

const card_type card::get_type() const
{
    return type;
}

void card::set_value(const int& input)
{
    this->value = input;
}

const int card::get_value() const
{
    return value;
}

void card::set_selected(const bool& input)
{
    this->selected = input;
}

const bool card::get_selected() const
{
    return selected;
}

QString card::get_type_string()
{
    switch (type)
    {
    case parrot:
        return "parrot";
    break;
    case gold:
        return "gold";
    break;
    case map:
        return "map";
    break;
    case flag:
        return "flag";
    break;
    case king:
        return "king";
    break;
    case queen:
        return "queen";
    break;
    case pirate:
        return "pirate";
    break;
    }
}
