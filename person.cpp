#include "person.h"

person::person()
{
    username = "";
    password = "";
    name = "" ;
    phone = "";
    email = "";
    coin = 0;
}

void person::set_username(QString input)
{
    username = input;
}

QString person::get_username()
{
    return username;
}

void person::set_password(QString input)
{
    password = input ;
}

QString person::get_password()
{
    return password;
}

void person::set_name(QString input)
{
    name = input;
}

QString person::get_name()
{
    return name;
}

void person::set_phone(QString input)
{
    phone = input;
}

QString person::get_phone()
{
    return phone;
}

void person::set_email(QString input)
{
    email = input;
}

QString person::get_email()
{
    return email;
}

void person::set_coin(int input)
{
    coin = input;
}

int person::get_coin()
{
    return coin;
}
