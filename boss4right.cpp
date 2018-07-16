#include "boss4right.h"

#include "laser.h"

#include <QTimer>

#include "math.h"

#include <stdlib.h> // rand

#include "game.h"

extern Game *game;

/*********************************************************************
 ** Level 4 boss (right side)
 ** Setting of target and shooting operates in levels - independent of
 ** either boss, as long as at least one is not dead.
 *********************************************************************/

Boss4Right::Boss4Right()
{
    setStartingHealth(6);

    setEnemyPix(QPixmap(":/images/images/dax.png"));
    setHealthPix(QPixmap(":/images/images/Mhb4.png"));

    setZValue(1);

    setSize("M");

    addToGroup(getEnemyPix());
    addToGroup(getHealthPix());

    setDimensions(109,94,0,-14);

    positionHealth();

    setPos(500,-getHeight());
    laser = new Laser();

    connect(game,SIGNAL(fire()),
            this,SLOT(shoot()));
    connect(game,SIGNAL(stopFiring()),
            this,SLOT(laserOff()));

    setMotion();
}

void Boss4Right::move()
{
    if(game->isPaused() == false){
        int minY = 30;
        int minX = 400;

        int maxX = 800 - getWidth() - 10;
        int maxY = 500;

        int speedMin = 3;
        int speedCap = 10;

        if(spawning){
            setPos(maxX, y() + 2);
            if(y() > minY){
                spawning = false;
            }
        }
        else{
            if(y() < maxY && !moveUp && y() > minY){ // continue moving down
                setPos(x(),y() + speed);
            }
            else if(y() >= maxY){ // change direction at bottom, move up
                setPos(x(),y()-speed);
                moveUp = true;
                setMoveLeft(true);
                speed = (rand() % speedCap) + speedMin; // change speed
            }
            else if(y() < maxY && y() > minY && moveUp && getMoveLeft() == true){ // keep moving up
                setPos(x(),y()-speed);
            }
            else if(y() <= minY && getMoveLeft() == true && x() > minX){ // start moving left
                setPos(x() - speed, y());
                moveUp = false;
                speed = (rand() % speedCap) + speedMin; // change speed
            }
            else if(y() <= minY && getMoveLeft() == true && x() > minX){ // continue moving left
                setPos(x() - speed, y());
            }
            else if(y() <= minY && getMoveLeft() == true && x() <= minX){ // switch to right
                setPos(x() + speed, y());
                setMoveLeft(false);
                speed = (rand() % speedCap) + speedMin; // change speed
            }
            else if(y() <= minY && getMoveLeft() == false && x() < maxX){ // keep moving right
                setPos(x() + speed, y());
                moveUp = false;
            }
            else if(y() <= minY && getMoveLeft() == false && x() >= maxX){ // start moving up
                setPos(x(),minY + speed);
                setMoveLeft(true);
                speed = (rand() % speedCap) + speedMin; // change speed
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
}

void Boss4Right::shoot()
{
    if(game->isPaused() == false){
        targetX = game->getTargetedX() + 43;
        targetY = game->getTargetedY() + 40;
        positionLaser();
        game->addToScene(laser);
    }
}


void Boss4Right::positionLaser()
{
    if(game->isPaused() == false){
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

            laser->setRotation(result);
        }
    }

}

void Boss4Right::laserOff()
{
    if(laser && game->isPaused() == false){
        game->removeFromScene(laser);
    }
}

void Boss4Right::laserOn()
{
    if(game->isPaused() == false){
        game->addToScene(laser);
    }
}

