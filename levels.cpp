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
#include "foe4.h"

#include "boss1.h"
#include "boss2.h"
#include "boss3.h"
#include "boss4left.h"
#include "boss4right.h"

// because we want to connect a timer to a function that constantly creates enemies
#include <QTimer>

extern Game * game;

/*********************************************************************
 **
 *********************************************************************/

// the levels class contains all of the logic for each level

levels::levels()
{
    //QTimer::singleShot(1000, this, SLOT(spawnBoss4()));
    //spawnBoss4();
    //spawnBoss3();
    //spawnBoss2();
    //spawnBoss3();
    level1();

    //level2();
    //level3();
    //level4();
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

void levels::spawnFoe4()
{
    Foe4 *enemy = new Foe4();
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
    QTimer::singleShot(2400, this, SLOT(spawnFoe1()));
    QTimer::singleShot(3400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(4400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(5400, this, SLOT(spawnFoe1()));
    QTimer::singleShot(6700, this, SLOT(spawnFoe2()));

    QTimer::singleShot(11400, this, SLOT(spawnBoss2()));
}

void levels::level3()
{
    QTimer::singleShot(400, this, SLOT(spawnFoe3()));
    QTimer::singleShot(1400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(2400, this, SLOT(spawnFoe1()));
    QTimer::singleShot(4000, this, SLOT(spawnFoe1()));
    QTimer::singleShot(5400, this, SLOT(spawnFoe1()));

    QTimer::singleShot(6400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(8400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(10400, this, SLOT(spawnFoe1()));
    QTimer::singleShot(12400, this, SLOT(spawnFoe1()));
    QTimer::singleShot(14400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(15000, this, SLOT(spawnFoe1()));
    QTimer::singleShot(19400, this, SLOT(spawnFoe3()));
    QTimer::singleShot(21400, this, SLOT(spawnFoe1()));



    QTimer::singleShot(24400, this, SLOT(spawnBoss3()));
}

void levels::level4()
{
    //game->invincibilityOn(); // modify!
    //QTimer::singleShot(400, this, SLOT(spawnBoss4()));
    QTimer::singleShot(400, this, SLOT(spawnFoe4()));
    QTimer::singleShot(2400, this, SLOT(spawnFoe4()));
    QTimer::singleShot(3400, this, SLOT(spawnFoe1()));
    QTimer::singleShot(4400, this, SLOT(spawnFoe2()));
    QTimer::singleShot(5400, this, SLOT(spawnFoe1()));
    QTimer::singleShot(6400, this, SLOT(spawnFoe3()));
    QTimer::singleShot(9400, this, SLOT(spawnFoe4()));

    QTimer::singleShot(15400, this, SLOT(spawnBoss4()));
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

void levels::spawnBoss3()
{
    Boss3 *enemy = new Boss3();

    connect(enemy,SIGNAL(bossDeath()),
            this,SLOT(level4()));

    game->addToScene(enemy);
}

void levels::spawnBoss4()
{
    Boss4Left * enemyLeft = new Boss4Left();
    game->addToScene(enemyLeft);

    Boss4Right *enemyRight = new Boss4Right();
    game->addToScene(enemyRight);

    connect(enemyLeft,SIGNAL(leftBossDeath()),
            enemyRight,SLOT(makeCalls()));

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            game,SLOT(targetFollow()));
    timer->start(6000);
}
