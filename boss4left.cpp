#include "boss4left.h"

#include "laser.h"

#include "target.h"

#include <QTimer>

#include <QDebug>

#include "math.h"

extern Game *game;

Boss4Left::Boss4Left()
{

    setStartingHealth(6);

    setEnemyPix(QPixmap(":/images/images/johnny.png"));
    setHealthPix(QPixmap(":/images/images/Mhb4.png"));

    setSize("M");

    addToGroup(getEnemyPix());
    addToGroup(getHealthPix());

    setDimensions(110,114,0,-10);

    positionHealth();

    setPos(0,0);
    laser = new Laser();

    setMotion();



    shoot();

    QTimer::singleShot(2400, this, SLOT(laserOff()));
}

void Boss4Left::move()
{
    if(game->isPaused() == false){
        if(x() < 5){
            setPos(x()+1,y());
        }

        if(((y() < 600-getHeight() && !moveUp) || (y() <= 0 && moveUp))){
            // change direction
            setPos(x(),y()+3);
            moveUp = false;
        }
        else if(((y() > 0 && moveUp) || (y() >= 600-getHeight() && !moveUp))){
            // change direction
            setPos(x(), y()-3);
            // set moveLeft
            moveUp = true;
        }

        positionLaser();

        checkStatus();

        if(isDead()){
            emit bossDeath();
            deleteLater();
        }
    }
}

void Boss4Left::shoot()
{
    target *newTarget = new target(3);
    newTarget->setPos(50,50);
    game->addToScene(newTarget);

    game->addToScene(laser);


}

void Boss4Left::positionLaser()
{
    if(laser){
        laser->setPos(x() + getWidth()/2 - 3, y() + getHeight()/2 - 3);

        double sourceX = x() + getWidth()/2 - 10;
        double sourceY = y() + getHeight()/2 - 10;
        targetX = 400;
        targetY = 400;

        double param = (targetY - sourceY)/(targetX - sourceX);

        double result = atan (param) * 180 / M_PI;

        laser->setRotation(result);



    }

}

void Boss4Left::laserOff()
{
    if(laser){
        game->removeFromScene(laser);
    }
}

void Boss4Left::laserOn()
{
    game->addToScene(laser);
}
