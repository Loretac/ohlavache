#include "foe4.h"

#include "bulletdirected.h"

#include "bulletminesmall.h"

#include <QTimer>


extern Game *game;

/*********************************************************************
 **
 *********************************************************************/

Foe4::Foe4()
{
    setStartingHealth(2);

//    setDimensions(100,53,10,-10);

//    setEnemyPix(QPixmap(":/images/images/ufo.png"));



    setDimensions(80,58,0,-10);
    setEnemyPix(QPixmap(":/images/images/fabian.png"));


    setHealthPix(QPixmap(":/images/images/Shb2.png"));

    setSize("S");

    addToGroup(getEnemyPix());
    addToGroup(getHealthPix());



    positionHealth();

    setPos(rand()% (800-getWidth()),-getHeight());

    setMotion();

    startShooting();
}

void Foe4::move()
{
    if(game->isPaused() == false){
        setPos(x(),y()+1);

        checkStatus();

        if(isDead()){
            deleteLater();
        }
    }
}

void Foe4::shoot()
{
    if(game->isPaused() == false){
        BulletMineSmall *Bullet = new BulletMineSmall();
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

}

void Foe4::startShooting()
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            this,SLOT(shoot()));

    timer->start(1500);
}
