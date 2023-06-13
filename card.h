#ifndef CARD_H
#define CARD_H

#include <QWidget>

enum card_type{parrot , gold , map , flag , king , queen , pirate};

class card : public QWidget
{
private :
    card_type type ;
    int value ;
    bool selected;

    Q_OBJECT
public:
    explicit card(QWidget *parent = nullptr);

signals:

};

#endif // CARD_H
