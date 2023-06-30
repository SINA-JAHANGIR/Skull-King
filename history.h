#ifndef HISTORY_H
#define HISTORY_H

#include <QMainWindow>

namespace Ui {
class history;
}

class history : public QMainWindow
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    ~history();

private:
    Ui::history *ui;
};

#endif // HISTORY_H
