#include "levels.h"
//#include "enemytemp.h"
#include "game.h"

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>

#include <QtDebug>

#include "enemy.h"
#include "foe1.h"
#include "foe2.h"
#include "foe3.h"

#include "boss1.h"
#include "boss2.h"

// because we want to connect a timer to a function that constantly creates enemies
#include <QTimer>

extern Game * game;

// the levels class contains all of the logic for each level

levels::levels()
{
    level1();

    //level2();
    //level3();
}

void levels::spawnFoe1()
{
    Foe1 *enemy = new Foe1();
    //activeItems.push_back(enemy);
    game->addToScene(enemy);
}

void levels::spawnFoe2()
{
    Foe2 *enemy = new Foe2();
    game->addToScene(enemy);
}

void levels::spawnFoe3()
{
    Foe3 *enemy = new Foe3();
    game->addToScene(enemy);
}

void levels::level1()
{
    QTimer::singleShot(400, this, SLOT(spawnFoe1()));

    QTimer::singleShot(1400, this, SLOT(spawnFoe1()));

    QTimer::singleShot(2400, this, SLOT(spawnFoe1()));
    QTimer::singleShot(3400, this, SLOT(spawnFoe1()));
    QTimer::singleShot(4400, this, SLOT(spawnFoe1()));
    QTimer::singleShot(5400, this, SLOT(spawnFoe1()));

    QTimer::singleShot(7400, this, SLOT(spawnBoss1()));


}

void levels::level2()
{
    QTimer::singleShot(400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(1400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(2400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(3400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(4400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(5400, this, SLOT(spawnFoe2()));

    QTimer::singleShot(7400, this, SLOT(spawnBoss2()));
}

void levels::level3()
{
    QTimer::singleShot(400, this, SLOT(spawnFoe3()));
}

void levels::spawnBoss1()
{
    Boss1 *enemy = new Boss1();

    connect(enemy, SIGNAL(bossDeath()),
            this,SLOT(level2()));
    game->addToScene(enemy);
}

void levels::spawnBoss2()
{
    Boss2 *enemy = new Boss2();

    connect(enemy,SIGNAL(bossDeath()),
            this,SLOT(level3()));
    game->addToScene(enemy);
}



// spawn minions for level 2
//void levels::spawn2()
//{
//    Enemy *enemy = new Enemy(3,2);

//    game->scene->addItem(enemy);
//}

// spawn minions for level 3
//void levels::spawn3()
//{
//    Enemy *enemy = new Enemy(5,4);

//    game->scene->addItem(enemy);
//}



//void levels::spawnBoss2()
//{
//    Enemy *enemy = new Enemy(4,4);
//    connect(enemy,SIGNAL(boss2Dead()),
//            this,SLOT(level3())
//    );

//    game->scene->addItem(enemy);
//}

//void levels::spawnBoss3()
//{
//    Enemy *enemy = new Enemy(6,10);

//    game->scene->addItem(enemy);
//}




//void levels::level2()
//{
//   QTimer::singleShot(400, this, SLOT(spawn2()));
//   QTimer::singleShot(1400, this, SLOT(spawn2()));
//   QTimer::singleShot(2400, this, SLOT(spawn2()));
//   QTimer::singleShot(3400, this, SLOT(spawn2()));
//   QTimer::singleShot(4400, this, SLOT(spawn2()));
//   QTimer::singleShot(5400, this, SLOT(spawn2()));

//   QTimer::singleShot(9400, this, SLOT(spawnBoss2()));

//   QTimer::singleShot(400, this, SLOT(spawnBoss2()));
//}

//void levels::level3()
//{
//    QTimer::singleShot(400, this, SLOT(spawn3()));

//    QTimer::singleShot(1900, this, SLOT(spawn2()));

//    QTimer::singleShot(2900, this, SLOT(spawn3()));

//    QTimer::singleShot(4900, this, SLOT(spawn3()));

//    QTimer::singleShot(5900, this, SLOT(spawn2()));

//    QTimer::singleShot(7900, this, SLOT(spawnBoss3()));

//    //QTimer::singleShot(400, this, SLOT(spawnBoss3()));
//}
