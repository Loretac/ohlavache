#include "boss3.h"

#include "bulletminelarge.h"

#include <QTimer>

#include <stdlib.h> // rand

extern Game *game;

Boss3::Boss3()
{
    setStartingHealth(6);

    setEnemyPix(QPixmap(":/images/images/johnny.png"));
    setHealthPix(QPixmap(":/images/images/Mhb4.png"));

    setSize("M");

    addToGroup(getEnemyPix());
    addToGroup(getHealthPix());

    setDimensions(110,114,0,-10);

    positionHealth();

    setPos(rand()% (800-getWidth()),-getHeight());

    setMotion();

    startShooting();


}

void Boss3::move()
{
    if(game->isPaused() == false){
        if(y() < 10){
            setPos(x(),y()+2);
        }

        if(((x() < 700 && !getMoveLeft()) || (x() <= 0 && getMoveLeft()))){
            // change direction
            setPos(x()+15,y());
            setMoveLeft(false);
        }
        else if((x() >= 700 && !getMoveLeft())){
            // change direction
            setPos(x()-15, y());
            // set moveLeft
            setMoveLeft(true);
            if(fireCounter%2 == 0){
                rapidFire();
            }
            fireCounter++;
        }
        else if(x() > 0 && getMoveLeft()){
            setPos(x()-15, y());
        }

        checkStatus();

        if(isDead()){
            emit bossDeath();
            deleteLater();
        }
    }
}

void Boss3::shoot()
{
    BulletMineLarge *Bullet = new BulletMineLarge();

    Bullet->setSpeed(3);

    int xSource = x() + getWidth()/2 - Bullet->getWidth()/2;
    int ySource = y() + getHeight()/2 - Bullet->getHeight()/2;

    // bullet moves straight down
    Bullet->setXTrajectory(0);
    Bullet->setYTrajectory(1);

    Bullet->setPos(xSource,ySource);

    game->addToScene(Bullet);
}

void Boss3::normalFire()
{
    QTimer::singleShot(300, this, SLOT(shoot()));
    QTimer::singleShot(450, this, SLOT(shoot()));
    QTimer::singleShot(600, this, SLOT(shoot()));
    QTimer::singleShot(750, this, SLOT(shoot()));
    QTimer::singleShot(900, this, SLOT(shoot()));
    QTimer::singleShot(1050, this, SLOT(shoot()));
    QTimer::singleShot(1200, this, SLOT(shoot()));
    QTimer::singleShot(1350, this, SLOT(shoot()));
    QTimer::singleShot(1500, this, SLOT(shoot()));
    QTimer::singleShot(1650, this, SLOT(shoot()));
    QTimer::singleShot(1800, this, SLOT(shoot()));


    QTimer::singleShot(2500, this, SLOT(rapidFire()));


}

void Boss3::rapidFire()
{
    int val = rand() % 11;

    if(val != 0){
        QTimer::singleShot(0, this, SLOT(shoot()));
    }
    if(val != 1 && val != 0){
        QTimer::singleShot(70, this, SLOT(shoot()));
    }
    if(val != 2 && val != 1){
        QTimer::singleShot(140, this, SLOT(shoot()));
    }
    if(val != 3 && val != 2){
        QTimer::singleShot(210, this, SLOT(shoot()));
    }
    if(val != 4 && val != 3){
        QTimer::singleShot(280, this, SLOT(shoot()));
    }
    if(val != 5 && val != 4){
        QTimer::singleShot(350, this, SLOT(shoot()));
    }
    if(val != 6 && val != 5){
        QTimer::singleShot(420, this, SLOT(shoot()));
    }
    if(val != 7 && val != 6){
        QTimer::singleShot(490, this, SLOT(shoot()));
    }
    if(val != 8 && val != 7){
        QTimer::singleShot(560, this, SLOT(shoot()));
    }
    if(val != 9 && val != 8){
        QTimer::singleShot(630, this, SLOT(shoot()));
    }
    if(val != 10 && val != 9){
        QTimer::singleShot(700, this, SLOT(shoot()));
    }
    if(val != 10){
        QTimer::singleShot(770, this, SLOT(shoot()));
    }
}

void Boss3::startShooting()
{
//    QTimer *timer = new QTimer();
//    connect(timer,SIGNAL(timeout()),
//            this,SLOT(shoot()));

//    timer->start(2475);

    //normalFire();




}
