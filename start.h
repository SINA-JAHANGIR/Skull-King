#ifndef START_H
#define START_H

#include <QMainWindow>

#include "server.h"
#include "client.h"
#include "start.h"

namespace Ui {
class start;
}

class start : public QMainWindow
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = nullptr);
    ~start();


private slots:
    void on_btn_host_clicked();
    void on_btn_join_clicked();

private:
    Ui::start *ui;
    server *host;
    client *join;
    QWidget *par;
};

#endif // START_H
