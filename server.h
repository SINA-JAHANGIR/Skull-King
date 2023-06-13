#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>

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

private:
    Ui::server *ui;
    QTcpServer *game_server;
    QTcpSocket *client_socket;
};

#endif // SERVER_H
