#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QVector>
#include <QVBoxLayout>
#include <QPropertyAnimation>

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
    void start();
    void round(int);
    void make_card(int);
    void dealer_animation();

private slots:
    void slo_forecast(int);
    void slo_selected_card(card);
    void slo_arrange_card();

private:
    Ui::game *ui;
    // Property :
    card all_cards[42];
    customized_button * all_cards_btn[42];
    player player1;
    player player2;
    QVector<customized_button *> all_forecast_btn;
    QVector<QPropertyAnimation *> all_move_animation;
    // Functions :
    void set_all_cards();
    void forecast(int);
};

#endif // GAME_H
