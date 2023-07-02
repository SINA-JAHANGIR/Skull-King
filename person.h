#ifndef PERSON_H
#define PERSON_H

#include <QString>

class person
{
private :
    QString username;
    QString password;
    QString name;
    QString phone;
    QString email;
    int coin;
public:
    person();
    void set_username(QString);
    QString get_username();
    void set_password(QString);
    QString get_password();
    void set_name(QString);
    QString get_name();
    void set_phone(QString);
    QString get_phone();
    void set_email(QString);
    QString get_email();
    void set_coin(int);
    int get_coin();
};

#endif // PERSON_H
