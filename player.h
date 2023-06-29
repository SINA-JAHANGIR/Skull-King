#ifndef PLAYER_H
#define PLAYER_H

#include "customized_button.h"
#include <QVector>
#include <QString>

typedef QVector<customized_button*>::iterator iter;

class player
{
private:
    QString username;
    int forecast_number;
    customized_button* selected_card_btn;
public:
    QVector<customized_button*> cards;
    QVector<customized_button*> win_cards;
    int score = 0;
    // Functions :
    player();
    void set_username(QString);
    QString get_username();
    void set_forecast_number(int);
    int get_forecast_number();
    void set_selected_card_btn(customized_button*);
    customized_button* get_selected_card_btn();
    void clear_cards();
    void clear_win_cards();
    void hide_cards();
    void hide_win_cards();
    iter find_card(customized_button*);
};

#endif // PLAYER_H
