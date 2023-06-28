#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>

#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <Thread>
#include <QSignalSpy>

#include "card.h"
#include "game.h"

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
    void slo_read_card();
    void slo_send_one_card(card);
    void slo_change_card();

private slots:
    void on_btn_start_clicked();

signals:
    void sig_continue();


private:
    Ui::client *ui;
    QTcpSocket *socket;
    game *game_client_page;
    std::thread thread;
    QSignalSpy* spy;

    // Functions :
    QByteArray card_to_qbytearray(const card&);
    card qbytearray_to_card(QByteArray&);
};

#endif // CLIENT_H
