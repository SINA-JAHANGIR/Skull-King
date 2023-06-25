#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QString>

enum card_type{parrot , gold , map , flag , king , queen , pirate};

class card : public QWidget
{
private :
    card_type type ;
    int value ;
    bool selected;
    int number;
    Q_OBJECT
public:
    explicit card(QWidget *parent = nullptr);
    card(const card&);
    // Functions :
    card operator=(const card&);
    bool operator>(const card&);
    void set_type(const card_type&);
    const card_type get_type() const;
    void set_value(const int&);
    const int get_value() const;
    void set_selected(const bool&);
    const bool get_selected() const;
    void set_number(const int&);
    const int get_number() const;
    QString get_type_string();
signals:

};

#endif // CARD_H
