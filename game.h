#ifndef GAME_H
#define GAME_H

#include <QMainWindow>

#include "card.h"
#include "player.h"

namespace Ui {
class game;
}

class game : public QMainWindow
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    ~game();

private slots:

private:
    Ui::game *ui;
    // Property :
    card all_cards[42];
    player player1;
    player player2;
    // Functions :
    void set_all_cards();
};

#endif // GAME_H
