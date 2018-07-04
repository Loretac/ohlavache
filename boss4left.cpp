#include "boss4left.h"

#include "laser.h"

#include "target.h"

#include <QTimer>

#include <QDebug>

#include "math.h"

#include <stdlib.h> // rand

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

    connect(game,SIGNAL(fire()),
            this,SLOT(shoot()));
    connect(game,SIGNAL(stopFiring()),
            this,SLOT(laserOff()));

    setMotion();

    //QTimer *timer = new QTimer(this);


    game->targetFollow();

    //shoot();

    //QTimer::singleShot(2400, this, SLOT(laserOff()));
}

void Boss4Left::move()
{
    if(game->isPaused() == false){
//        if(x() < 5){
//            setPos(x()+1,y());
//        }

        int minY = 30;
        int minX = 10;

        int maxX = 300;
        int maxY = 500;

        int speedMin = 3;
        int speedCap = 10;

        if(y() < maxY && y() > minY && !moveUp){ //continue moving down
            setPos(x(),y()+speed);
            //qDebug() << "case 1";
        }
        else if(y() >= maxY){ // change direction at bottom, move up
            setPos(x(),y()-speed);
            moveUp = true;
            speed = (rand() % speedCap) + speedMin; // change speed
            //qDebug() << "case 2";
        }
        else if(y() < maxY && y() > minY && moveUp && getMoveLeft() == false){ // keep moving up
            setPos(x(),y()-speed);
            //qDebug() << "case 3";
        }
        else if(y() <= minY && getMoveLeft() == false && x() < minX){ // start moving right
            setPos(x() + speed, y());
            moveUp = false;
            speed = (rand() % speedCap) + speedMin; // change speed
            //qDebug() << "case 4";
        }
        else if(y() <= minY && getMoveLeft() == false && x() < maxX){ // continue moving right
            setPos(x() + speed, y());
            //qDebug() << "case 5";
        }
        else if(y() <= minY && getMoveLeft() == false && x() >= maxX){ // switch to left
            setPos(x() - speed, y());
            setMoveLeft(true);
            speed = (rand() % speedCap) + speedMin; // change speed
            //qDebug() << "case 6";
        }
        else if(y() <= minY && getMoveLeft() == true && x() > minX){ // keep moving left
            setPos(x() - speed, y());
            setMoveLeft(true);
            moveUp = false;
            //qDebug() << "case 7";
        }
        else if(y() <= minY && getMoveLeft() == true && x() <= minX){ // start moving up
            setPos(x(),minY + speed);
            setMoveLeft(false);
            speed = (rand() % speedCap) + speedMin; // change speed
            //qDebug() << "case 8";
        }

        positionLaser();

        checkStatus();

        if(isDead()){
            emit leftBossDeath();
            laser->deleteLater();
            deleteLater();
        }
    }
}

void Boss4Left::shoot()
{
    if(game->isPaused() == false){
        targetX = game->getTargetedX() + 43;
        targetY = game->getTargetedY() + 40;
        positionLaser();
        game->addToScene(laser);
    }
}

void Boss4Left::setTarget()
{
    game->targetFollow();
}

void Boss4Left::positionLaser()
{
    if(game->isPaused() == false){
        if(laser){
            laser->setPos(x() + getWidth()/2 - 3, y() + getHeight()/2 - 3);



            double sourceX = x() + getWidth()/2 - 10;
            double sourceY = y() + getHeight()/2 - 10;

            double x = targetX - sourceX;
            double y = targetY - sourceY;


            double param = y/x;


            double result = atan (param) * 180 / M_PI;

            if(x < 0){
                result += 180;
            }

            laser->setRotation(result);
        }
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
