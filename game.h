#ifndef GAME_H
#define GAME_H

#include <QMainWindow>

namespace Ui {
class game;
}

class game : public QMainWindow
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    ~game();

private:
    Ui::game *ui;
};

#endif // GAME_H
