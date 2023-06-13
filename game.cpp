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
