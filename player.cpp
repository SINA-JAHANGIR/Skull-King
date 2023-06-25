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
