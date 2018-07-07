#include "boss2.h"
#include "target.h"
#include "bullettargetedlarge.h"

#include <QTimer>

#include <math.h>

extern Game *game;

/*********************************************************************
 **
 *********************************************************************/

Boss2::Boss2()
{
    setStartingHealth(12);

    setDimensions(157,225,25,-14);

    setEnemyPix(QPixmap(":/images/images/gideon.png"));
    setHealthPix(QPixmap(":/images/images/Mhb4.png"));

    setSize("M");

    addToGroup(getEnemyPix());
    addToGroup(getHealthPix());



    positionHealth();

    setPos(rand()% (800-getWidth()),-getHeight());

    setMotion();

    startShooting();
}

void Boss2::move()
{
    if(game->isPaused() == false){
        if(y() < 20){
            setPos(x(),y() + 2);
        }

        if(((x() < 700 && !getMoveLeft()) || (x() <= 0 && getMoveLeft()))){
            // change direction
            setPos(x()+10,y());
            setMoveLeft(false);
        }
        else if(((x() > 0 && getMoveLeft()) || (x() >= 700 && !getMoveLeft()))){
            // change direction
            setPos(x()-10, y());
            // set moveLeft
            setMoveLeft(true);
        }

        checkStatus();

        if(isDead()){
            emit bossDeath();
            deleteLater();
        }
    }
}

void Boss2::shoot()
{
    if(game->isPaused() == false){
        BulletTargetedLarge *Bullet = new BulletTargetedLarge();

        Bullet->setSpeed(3);

        // coordinates of origin of bullet
        double xSource = x() + getWidth()/2 - Bullet->getWidth()/2;
        double ySource = y() + getHeight()/2 - Bullet->getHeight()/2;

        // coordinates of center of player
        double xPlayer = game->getPlayerXPos() + game->getPlayerWidth()/2 - Bullet->getWidth()/2;
        double yPlayer = game->getPlayerYPos() + game->getPlayerHeight()/2 - Bullet->getHeight()/2;

        // set the trajectory of the bullet
        Bullet->setXTrajectory(xPlayer-xSource);
        Bullet->setYTrajectory(yPlayer-ySource);

        // bullet starts at source
        Bullet->setPos(xSource,ySource);

        // START TESTING
        Bullet->setTransformOriginPoint(Bullet->getWidth()/2,Bullet->getHeight()/2);

        double x = xPlayer - xSource;
        double y = yPlayer - ySource;

        double angle = (atan(y/x)) * 180 / M_PI;

        if(x < 0){
            angle += 90;
        }
        if(x > 0){
            angle -= 90;
        }

        Bullet->setRotation(angle);
        //END TESTING


        // add a target
        target *newTarget = new target(1);

        game->addToScene(newTarget);

        // when the bullet arrives, destroy the target
        connect(Bullet,SIGNAL(arrived()),
                newTarget,SLOT(boom()));

        connect(Bullet,SIGNAL(collide()),
                newTarget,SLOT(collision()));

        game->addToScene(Bullet);
    }

}

void Boss2::startShooting()
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            this,SLOT(shoot()));


    timer->start(2475);
}
