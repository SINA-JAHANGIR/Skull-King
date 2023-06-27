#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QByteArray>
#include <QDataStream>
#include <thread>
#include <QSignalSpy>


#include "game.h"
#include "customized_button.h"
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
    void slo_send_card();
    void slo_send_one_card(card);
    void slo_read_card();

private slots:
    void on_btn_start_clicked();

signals:
    void sig_continue();

private:
    Ui::server *ui;
    QTcpServer *game_server;
    QTcpSocket *client_socket;
    game *game_server_page;
    bool ready = false;
    std::thread thread;
    QSignalSpy* spy;
    // Functions :
    QByteArray card_to_qbytearray(const card&);
    card qbytearray_to_card(QByteArray&);
};

#endif // SERVER_H
