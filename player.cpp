#include "player.h"

player::player()
{
    username = "";
}

void player::set_username(QString input)
{
    username = input ;
}

QString player::get_username()
{
    return username;
}

/*
void player::set_cards(QVector<customized_button*> input)
{
    cards = input;
}

QVector<customized_button*> player::get_cards()
{
    return cards;
}
*/
