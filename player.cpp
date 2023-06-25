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

void player::set_selected_card(customized_button * input)
{
    selected_card = input;
}

customized_button* player::get_selected_card()
{
    return selected_card;
}

iter player::find_card(customized_button* input)
{
    for (iter i = cards.begin() ; i != cards.end() ; i++)
    {
        if (*i == input)
        {
            return i;
        }
    }
   return cards.end();
}
