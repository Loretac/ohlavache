#include "bullettargetedlarge.h"
#include "game.h"

#include <math.h>

#include <QDebug>

extern Game *game;

/*********************************************************************
 ** SHOT BY BOSS 2
 *********************************************************************/

BulletTargetedLarge::BulletTargetedLarge()
{
    setDimensions(25,62);
    setBulletPix(QPixmap(":/images/images/missile.png"));

    setMotion();
}

void BulletTargetedLarge::move()
{
    if(game->isPaused() == false){
        if(game->isInvincible() == false){
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
