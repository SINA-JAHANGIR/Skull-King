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
    customized_button* selected_card;
public:
    QVector<customized_button*> cards;
    player();
    // Functions :
    void set_username(QString);
    QString get_username();
    void set_forecast_number(int);
    int get_forecast_number();
    void set_selected_card(customized_button*);
    customized_button* get_selected_card();
    iter find_card(customized_button*);
};

#endif // PLAYER_H
