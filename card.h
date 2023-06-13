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
    // Functions :
    void set_type(const card_type&);
    const card_type get_type();
    void set_value(const int&);
    const int get_value();
    void set_selected(const bool&);
    const bool get_selected();


signals:

};

#endif // CARD_H
