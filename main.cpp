#include <QApplication>
#include "game.h"



/*********************************************************************
 ** This program is a space shooter game, similar to Galaga. For
 ** more information, see the ReadMe.
 *********************************************************************/
Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();

    return a.exec();
}
