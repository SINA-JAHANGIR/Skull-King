#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QByteArray>
#include <QDataStream>
#include <thread>
#include <QThread>
#include <QSignalSpy>


#include "game.h"
#include "customized_button.h"
#include "card.h"
#include "person.h"

namespace Ui {
class server;
}

class server : public QMainWindow
{
    Q_OBJECT

public:
    explicit server(person,QWidget *parent = nullptr);
    ~server();

public slots:
    void connection_new();
    void slo_send_card();
    void slo_send_one_card(card);
    void slo_read_card();
    void slo_change_card();
    void slo_change_request();
    void slo_send_forecast();
    void slo_end_of_round();
    void slo_finish_animation();
    void slo_stop();
    void slo_resume();
    void slo_exit();

private slots:
    void on_btn_start_clicked();

signals:
    void sig_continue();
    void sig_change_request();
    void sig_game_continue();
    void sig_get_forecast();
    void sig_stop();
    void sig_resume();
    void sig_exit();

private:
    Ui::server *ui;
    QTcpServer *game_server;
    QTcpSocket *client_socket;
    game *game_server_page;
    bool ready = false;
    std::thread thread;
    QSignalSpy* spy;
    QWidget *par;
    person person1;
    int num_player = 1 ;
    // Functions :
    QByteArray card_to_qbytearray(const card&);
    card qbytearray_to_card(QByteArray&);
    void change_card();
};

#endif // SERVER_H
