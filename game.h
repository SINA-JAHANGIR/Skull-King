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
    void make_card(int);
    void dealer_animation();

private slots:
    void slo_forecast(int);
    void slo_selected_card(customized_button*);
    void slo_p1_arrange_card();
    void slo_p2_arrange_card();
    void slo_active_click();

signals:
    void sig_send_card();

private:
    Ui::game *ui;
    // Property :
    card all_cards[56];
    customized_button * all_cards_btn[56];
    player player1;
    player player2;
    QVector<customized_button *> all_forecast_btn;
    QVector<QPropertyAnimation *> all_move_animation;
    // Functions :
    void set_all_cards();
    void sort_btn_cards(QVector<customized_button*>&);
    void clear_move_animations();
    void forecast(int);
    void change_StyleSheet(customized_button*);
    void inactive_click();
    friend class client;
    friend class server;
};

#endif // GAME_H
