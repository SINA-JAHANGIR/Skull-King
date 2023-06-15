#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QByteArray>
#include <QDataStream>
#include "game.h"

#include "card.h"

namespace Ui {
class server;
}

class server : public QMainWindow
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    ~server();

public slots:
    void connection_new();

private slots:
    void on_btn_start_clicked();

private:
    Ui::server *ui;
    QTcpServer *game_server;
    QTcpSocket *client_socket;
    game *game_page;
    bool ready = false;
    // Functions :
    QByteArray card_to_qbytearray(const card&);
    card qbytearray_to_card(QByteArray&);
};

#endif // SERVER_H
