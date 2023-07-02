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
#include "person.h"

namespace Ui {
class client;
}

class client : public QMainWindow
{
    Q_OBJECT

public:
    explicit client(person,QWidget *parent = nullptr);
    ~client();

public slots:
    void connected_to_server();
    void slo_read_card();
    void slo_send_one_card(card);
    void slo_change_card();
    void slo_send_forecast();
    void slo_call_dealer_animation();
    void slo_finish_animation();
    void slo_change_request();
    void slo_stop();
    void slo_resume();
    void slo_exit();

private slots:

    void on_pushButton_clicked();

signals:
    void sig_continue();
    void sig_game_continue();
    void sig_start();
    void sig_get_forecast();
    void sig_change_request();
    void sig_stop();
    void sig_resume();
    void sig_exit();


private:
    Ui::client *ui;
    QTcpSocket *socket;
    game *game_client_page;
    std::thread thread;
    QSignalSpy* spy;
    QWidget *par;
    QThread *qth;
    person person1;
    // Functions :
    QByteArray card_to_qbytearray(const card&);
    card qbytearray_to_card(QByteArray&);
};

#endif // CLIENT_H
