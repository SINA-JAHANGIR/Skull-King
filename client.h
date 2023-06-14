#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>

#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

#include "card.h"

namespace Ui {
class client;
}

class client : public QMainWindow
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();

public slots:
    void connected_to_server();

private:
    Ui::client *ui;
    QTcpSocket *socket;
    // Functions :
    QByteArray card_to_qbytearray(const card&);
    card qbytearray_to_card(QByteArray&);
};

#endif // CLIENT_H
