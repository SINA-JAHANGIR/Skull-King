#include "game_logo.h"
#include <QApplication>
#include <QForeach>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game_logo logo;
    logo.setWindowTitle("Skull King");
    logo.show();
    return a.exec();
}
