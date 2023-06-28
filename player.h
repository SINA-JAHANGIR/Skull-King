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
    player();
    // Functions :
    void set_username(QString);
    QString get_username();
    void set_forecast_number(int);
    int get_forecast_number();
    void set_selected_card_btn(customized_button*);
    customized_button* get_selected_card_btn();
    iter find_card(customized_button*);
};

#endif // PLAYER_H
