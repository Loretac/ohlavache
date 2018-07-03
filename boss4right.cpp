#include "boss4right.h"

#include "laser.h"

#include "target.h"

#include <QTimer>

#include <QDebug>

#include "math.h"

extern Game *game;

Boss4Right::Boss4Right()
{
    setStartingHealth(6);

    setEnemyPix(QPixmap(":/images/images/johnny.png"));
    setHealthPix(QPixmap(":/images/images/Mhb4.png"));

    setSize("M");

    addToGroup(getEnemyPix());
    addToGroup(getHealthPix());

    setDimensions(110,114,0,-10);

    positionHealth();

    setPos(800-getWidth(),600-getHeight());
    laser = new Laser();

    connect(game,SIGNAL(fire()),
            this,SLOT(shoot()));

    setMotion();
}

void Boss4Right::move()
{
    if(game->isPaused() == false){
        if(((y() < 600-getHeight() && !moveUp) || (y() <= 0 && moveUp))){
            // change direction
            setPos(x(),y()+6);
            moveUp = false;
        }
        else if(((y() > 0 && moveUp) || (y() >= 600-getHeight() && !moveUp))){
            // change direction
            setPos(x(), y()-6);
            // set moveLeft
            moveUp = true;
        }

        positionLaser();

        checkStatus();

        if(isDead()){
            emit rightBossDeath();
            laser->deleteLater();
            deleteLater();
        }
    }


}

void Boss4Right::shoot()
{
    targetX = game->getTargetedX() + 43;
    targetY = game->getTargetedY() + 40;
    positionLaser();
    game->addToScene(laser);
}

void Boss4Right::setTarget()
{
    game->targetFollow();
}

void Boss4Right::positionLaser()
{
    if(laser){
        laser->setPos(x() + getWidth()/2 - 3, y() + getHeight()/2 - 3);

        double sourceX = x() + getWidth()/2 - 10;
        double sourceY = y() + getHeight()/2 - 10;

        /*   angle to rotate:
        theta = arctan (x/y) + 90deg
        x = sourceX - targetX
        y = targetY - sourceY    */

        double y = targetY - sourceY;
        double x = sourceX - targetX;

        double param = x/y;
        double result = (atan (param) * 180 / M_PI) + 90;

        if(y < 0){
            result += 180;
        }

        qDebug() << result;
        laser->setRotation(result);
    }
}

void Boss4Right::laserOff()
{
    if(laser){
        game->removeFromScene(laser);
    }
}

void Boss4Right::laserOn()
{
    game->addToScene(laser);
}
