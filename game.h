#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "myrect.h"


class Game: public QGraphicsView{
  public:
    Game(QWidget *parent = 0);

    QGraphicsScene *scene;
    MyRect *player;

};

#endif // GAME_H
