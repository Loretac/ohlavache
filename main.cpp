#include <QApplication>
#include "game.h"





/*
 * QGraphicsScene
 * QGraphicsItem (QGraphicsRectItem - inherits from QGraphicsItem abstract class)
 * QGraphicsView
 *
 *
 * Created based on tutorial from Abdullah Aghazadah
 * Youtube channel:
 * https://www.youtube.com/channel/UClzV7jGJREjvCTzfGTrdrkQ
 *
 * */

Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();

    return a.exec();
}
