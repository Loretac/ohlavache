#include "foe2.h"

#include "game.h"
#include "bulletdirected.h"
#include <QTimer>

extern Game *game;

Foe2::Foe2()
{
    setStartingHealth(2);

    // BENI
    setDimensions(113,40,16,-14);
    setEnemyPix(QPixmap(":/images/images/beni.png"));
    // END BENI

    setHealthPix(QPixmap(":/images/images/Shb2.png"));

    setSize("S");

    addToGroup(getEnemyPix());
    addToGroup(getHealthPix());



    positionHealth();

    setPos(rand()% (800-getWidth()),-getHeight());

    setMotion();

    startShooting();
}

void Foe2::move()
{
    if(game->isPaused() == false){

        setPos(x(),y()+1.3);

        checkStatus();

        if(isDead()){
            deleteLater();
        }
    }
}

void Foe2::shoot()
{
   BulletDirected *Bullet = new BulletDirected();
   Bullet->setSpeed(5);

   // coordinates of origin of bullet
   int xSource = x() + getWidth()/2 - Bullet->getWidth()/2;
   int ySource = y() + getHeight()/2 - Bullet->getHeight()/2;

   // coordinates of center of player (offset for center of bullet)
   int xPlayer = game->getPlayerXPos() + game->getPlayerWidth()/2 - Bullet->getWidth()/2;
   int yPlayer = game->getPlayerYPos() + game->getPlayerHeight()/2 - Bullet->getHeight()/2;

   // set the trajectory of the bullet
   Bullet->setXTrajectory(xPlayer-xSource);
   Bullet->setYTrajectory(yPlayer-ySource);

   // bullet starts at source
   Bullet->setPos(xSource,ySource);

   game->addToScene(Bullet);
}

void Foe2::startShooting()
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            this,SLOT(shoot()));

    timer->start(1500);
}
