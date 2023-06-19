#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QVector>

#include "customized_button.h"
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
    // Functions :
    void first_round();

private slots:
    void slo_forecast(int);

private:
    Ui::game *ui;
    // Property :
    card all_cards[42];
    customized_button * all_cards_btn[42];
    player player1;
    player player2;
    QVector<customized_button *> all_forecast_btn;
    // Functions :
    void set_all_cards();
    void forecast(int);
};

#endif // GAME_H
