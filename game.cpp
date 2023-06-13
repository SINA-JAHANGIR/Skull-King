#include "game.h"
#include "ui_game.h"

game::game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
}

game::~game()
{
    delete ui;
}

void game::set_all_cards()
{
    for (int i = 0 ; i < 8 ; i++)
    {
        all_cards[i].set_value(i+1);
        all_cards[i].set_type(parrot);
    }
    for (int i = 8 ; i < 16 ; i++)
    {
        all_cards[i].set_value(i-7);
        all_cards[i].set_type(gold);
    }
    for (int i = 16 ; i < 24 ; i++)
    {
        all_cards[i].set_value(i-15);
        all_cards[i].set_type(map);
    }
    for (int i = 24 ; i < 32 ; i++)
    {
        all_cards[i].set_value(i-23);
        all_cards[i].set_type(flag);
    }
    for (int i = 32 ; i < 36 ; i++)
    {
        all_cards[i].set_value(i-31);
        all_cards[i].set_type(pirate);
    }
    for (int i = 36 ; i < 39 ; i++)
    {
        all_cards[i].set_value(i-35);
        all_cards[i].set_type(king);
    }
    for (int i = 39 ; i < 42 ; i++)
    {
        all_cards[i].set_value(i-38);
        all_cards[i].set_type(queen);
    }
}
