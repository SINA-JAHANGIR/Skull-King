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


void player::set_forecast_number(int input)
{
    forecast_number = input;
}

int player::get_forecast_number()
{
    return forecast_number;
}

void player::set_selected_card_btn(customized_button * input)
{
    selected_card_btn = input;
}

customized_button* player::get_selected_card_btn()
{
    return selected_card_btn;
}

void player::clear_cards()
{
    for (iter i = cards.begin() ; i < cards.end() ; i++)
    {
        cards.erase(i);
    }
}

void player::clear_win_cards()
{
    for (iter i = win_cards.begin() ; i < win_cards.end() ; i++)
    {
        win_cards.erase(i);
    }
}

void player::hide_cards()
{
    for (int i = 0 ; i < cards.size() ; i++)
    {
        cards[i]->hide();
    }
}

void player::hide_win_cards()
{
    for (int i = 0 ; i < win_cards.size() ; i++)
    {
        win_cards[i]->hide();
    }
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
