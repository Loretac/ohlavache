#include "foe3.h"

#include "bullettargetedsmall.h"
#include "target.h"

#include <QTimer>

extern Game *game;

Foe3::Foe3()
{
    setStartingHealth(2);

    setEnemyPix(QPixmap(":/images/images/ufo.png"));
    setHealthPix(QPixmap(":/images/images/Shb2.png"));

    setSize("S");

    addToGroup(getEnemyPix());
    addToGroup(getHealthPix());

    setDimensions(100,53,10,-10);

    positionHealth();

    setPos(rand()% (800-getWidth()),-getHeight());

    setMotion();

    startShooting();
}

void Foe3::move()
{
    if(game->isPaused() == false){
        setPos(x(),y()+1.3);

        checkStatus();

        if(isDead()){
            deleteLater();
        }
    }
}

void Foe3::shoot()
{
    BulletTargetedSmall *Bullet = new BulletTargetedSmall();

    Bullet->setSpeed(5);

    // coordinates of origin of bullet
    int xSource = x() + getWidth()/2 - Bullet->getWidth()/2;
    int ySource = y() + getHeight()/2 - Bullet->getHeight()/2;

    // coordinates of center of player
    int xPlayer = game->getPlayerXPos() + game->getPlayerWidth()/2 - Bullet->getWidth()/2;
    int yPlayer = game->getPlayerYPos() + game->getPlayerHeight()/2 - Bullet->getHeight()/2;

    // set the trajectory of the bullet
    Bullet->setXTrajectory(xPlayer-xSource);
    Bullet->setYTrajectory(yPlayer-ySource);

    // bullet starts at source
    Bullet->setPos(xSource,ySource);

    // add a target
    target *newTarget = new target(2);

    game->addToScene(newTarget);

    // when the bullet arrives, destroy the target
    connect(Bullet,SIGNAL(arrived()),
            newTarget,SLOT(smallBoom()));

    connect(Bullet,SIGNAL(collide()),
            newTarget,SLOT(smallCollision()));

    game->addToScene(Bullet);
}

void Foe3::startShooting()
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            this,SLOT(shoot()));


    timer->start(1875);
}
