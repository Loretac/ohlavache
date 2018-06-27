#include "levels.h"
#include "enemy.h"
#include "game.h"

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>

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

// spawn minions for level 1
void levels::spawn1()
{
    // group the items together......
    Enemy *enemy = new Enemy(1,2);

    game->scene->addItem(enemy); // only need to add the parent
}

// boss for level 1
void levels::spawnBoss1()
{
    Enemy *enemy = new Enemy(2,8);
    connect(enemy,SIGNAL(boss1Dead()),
            this,SLOT(level2())
    );

    game->scene->addItem(enemy); // add to the scene
}

// spawn minions for level 2
void levels::spawn2()
{
    Enemy *enemy = new Enemy(3,2);

    game->scene->addItem(enemy);
}

void levels::spawnBoss2()
{
    Enemy *enemy = new Enemy(4,4);

    game->scene->addItem(enemy);
}





void levels::level1()
{
    QTimer::singleShot(400, this, SLOT(spawn1()));
    QTimer::singleShot(1400, this, SLOT(spawn1()));

    QTimer::singleShot(2400, this, SLOT(spawn1()));
    QTimer::singleShot(3400, this, SLOT(spawn1()));
    QTimer::singleShot(4400, this, SLOT(spawn1()));
    QTimer::singleShot(5400, this, SLOT(spawn1()));

    QTimer::singleShot(9400, this, SLOT(spawnBoss1()));

}


void levels::level2()
{
   QTimer::singleShot(400, this, SLOT(spawn2()));
   QTimer::singleShot(1400, this, SLOT(spawn2()));
   QTimer::singleShot(2400, this, SLOT(spawn2()));
   QTimer::singleShot(3400, this, SLOT(spawn2()));
   QTimer::singleShot(4400, this, SLOT(spawn2()));
   QTimer::singleShot(5400, this, SLOT(spawn2()));

   QTimer::singleShot(9400, this, SLOT(spawnBoss2()));

    //QTimer::singleShot(400, this, SLOT(spawnBoss2()));
}
