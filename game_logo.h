#ifndef GAME_LOGO_H
#define GAME_LOGO_H

#include <QMainWindow>
#include <QLabel>
#include <QPropertyAnimation>

namespace Ui {
class game_logo;
}

class game_logo : public QMainWindow
{
    Q_OBJECT

public:
    explicit game_logo(QWidget *parent = nullptr);
    ~game_logo();
public slots:
    void slo_next_page();
private:
    Ui::game_logo *ui;
    QPropertyAnimation* animation;
    QLabel* lbl_logo;
};

#endif // GAME_LOGO_H
