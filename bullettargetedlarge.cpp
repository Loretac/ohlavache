#include "bullettargetedlarge.h"
#include <math.h>

#include <QDebug>

extern Game *game;

BulletTargetedLarge::BulletTargetedLarge()
{
    setDimensions(50,50);
    setBulletPix(QPixmap(":/images/images/timebomb.png"));

    setMotion();
}

void BulletTargetedLarge::move()
{
    if(game->isPaused() == false){
        QList<QGraphicsItem *> colliding_items = collidingItems();

        // Check if the bullet is colliding with the player
        for(int i = 0, n = colliding_items.size(); i < n; ++i){
            if(typeid(*(colliding_items[i])) == typeid(Player)){

                // signals to explode and destroy target
                emit collide();

                game->death();

                deleteLater();
                return;
            }
         }

        double pythagorean = sqrt((getXTrajectory()*getXTrajectory())+(getYTrajectory()*getYTrajectory()));

        setPos(x()+(getXTrajectory())*getSpeed()/pythagorean,y()+(getYTrajectory())*getSpeed()/pythagorean);

        setCounter(getCounter()+1);

        if(getCounter() >= pythagorean / getSpeed()){
            emit arrived();
            deleteLater();
            return;
        }

        checkStatus();


    }
}
