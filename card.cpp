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
    this->set_number(input.get_number());
}

card card::operator=(const card& input)
{
    this->set_type(input.get_type());
    this->set_value(input.get_value());
    this->set_selected(input.get_selected());
    this->set_number(input.get_number());
    return *this;
}

bool card::operator>(const card & input)
{
    switch(type)
    {
    case parrot :
                switch (input.type)
                {
                case parrot :
                    if (value > input.value)
                        return true;
                    else
                        return false;
                    break;
                case gold :
                case map :
                    return true;
                    break;
                default :
                    return false;
                }
    break;
    case gold :
                switch (input.type)
                {
                case gold :
                    if (value > input.value)
                        return true;
                    else
                        return false;
                    break;
                case parrot :
                case map :
                    return true;
                    break;
                default :
                    return false;
                }
    break;
    case map :
                switch (input.type)
                {
                case map :
                    if (value > input.value)
                        return true;
                    else
                        return false;
                    break;
                case parrot :
                case gold :
                    return true;
                    break;
                default :
                    return false;
                }
    break;
    case flag :
                switch (input.type)
                {
                case flag :
                    if (value > input.value)
                        return true;
                    else
                        return false;
                    break;
                case parrot :
                case gold :
                case map :
                    return true;
                    break;
                default :
                    return false;
                }
    break;
    case pirate :
    if (input.type == king)
        return false;
    else
        return true;
    break;
    case queen :
    if (input.type == pirate)
        return false;
    else
        return true;
    break;
    case king :
    if (input.type == queen)
        return false;
    else
        return true;
    break;
    }
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


void card::set_number(const int& input)
{
    number = input;
}

const int card::get_number() const
{
    return number;
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
