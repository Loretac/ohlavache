#include "levels.h"
#include "enemy.h"
#include "game.h"

#include <QtDebug>

// because we want to connect a timer to a function that constantly creates enemies
#include <QTimer>

extern Game * game;

// the levels class contains all of the logic for each level

levels::levels()
{
    level1();
    //level2();
}

void levels::spawn1()
{
    Enemy *enemy = new Enemy(1);
    game->scene->addItem(enemy); // add to the scene
}

void levels::spawn2()
{
    Enemy *enemy = new Enemy(2);
    game->scene->addItem(enemy); // add to the scene
}



void levels::level1()
{
    QTimer::singleShot(400, this, SLOT(spawn1()));
    QTimer::singleShot(800, this, SLOT(spawn1()));

    QTimer::singleShot(1200, this, SLOT(spawn1()));
   // QTimer::singleShot(1600, this, SLOT(spawn1()));
    //QTimer::singleShot(2000, this, SLOT(spawn1()));
    //QTimer::singleShot(2400, this, SLOT(spawn1()));



    //QTimer::singleShot(1600, this, SLOT(spawn2()));
    //QTimer::singleShot(2000, this, SLOT(spawn2()));
    //QTimer::singleShot(2400, this, SLOT(spawn2()));
    //QTimer::singleShot(2800, this, SLOT(spawn2()));
    //QTimer::singleShot(3200, this, SLOT(spawn2()));
}

void levels::level2()
{
   // QTimer::singleShot(400, this, SLOT(spawn2()));
}
