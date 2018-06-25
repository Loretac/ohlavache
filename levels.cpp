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
}

void levels::spawn1()
{
    // group the items together......
    Enemy *enemy = new Enemy(1,2);

    //QGraphicsPixmapItem *healthbar = new QGraphicsPixmapItem();
    //healthbar->setPixmap(QPixmap(":/images/images/Smallhealthbar.png"));


    //healthbar->setParentItem(enemy);

    //healthbar->setPos(10,-10);


    game->scene->addItem(enemy); // only need to add the parent
}

// boss for level 1
void levels::spawn2()
{
    Enemy *enemy = new Enemy(2,4);
    connect(enemy,SIGNAL(bossDead()),
            this,SLOT(level2())
    );

    game->scene->addItem(enemy); // add to the scene
}



void levels::level1()
{
    QTimer::singleShot(400, this, SLOT(spawn1()));
    QTimer::singleShot(1400, this, SLOT(spawn1()));

    QTimer::singleShot(2400, this, SLOT(spawn1()));
    QTimer::singleShot(3400, this, SLOT(spawn1()));
    QTimer::singleShot(4400, this, SLOT(spawn1()));
    QTimer::singleShot(5400, this, SLOT(spawn1()));

    QTimer::singleShot(7400, this, SLOT(spawn2()));

}


void levels::level2()
{
   QTimer::singleShot(400, this, SLOT(spawn1()));
}
