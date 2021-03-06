#include "boss1.h"
#include "bulletsimple.h"

#include <stdlib.h> // rand
#include <QTimer>

#include "game.h"

extern Game * game;

/*********************************************************************
 ** Level 1 boss
 *********************************************************************/

Boss1::Boss1()
{
    setStartingHealth(6);

    setDimensions(110,114,0,-10);

    setEnemyPix(QPixmap(":/images/images/johnny.png"));
    setHealthPix(QPixmap(":/images/images/Mhb4.png"));

    setSize("M");

    addToGroup(getEnemyPix());
    addToGroup(getHealthPix());



    positionHealth();

    setPos(rand()% (800-getWidth()),-getHeight());

    setMotion();

    startShooting();
}

void Boss1::move()
{
    if(game->isPaused() == false){
        if(y() < 20){
            setPos(x(),y()+2);
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

void Boss1::startShooting()
{
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,[this](){
        if(game->isPaused() == false){
            BulletSimple *Bullet = new BulletSimple();
            Bullet->setSpeed(1);
            Bullet->setXTrajectory(0);
            Bullet->setYTrajectory(1);
            Bullet->setPos(x()+getWidth()/2,y()+getHeight()/2); // offset for character
            game->addToScene(Bullet);
        }
    });

    timer->start(475);
}
