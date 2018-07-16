#include "bulletdirected.h"
#include "game.h"

#include <math.h>

extern Game *game;

/*********************************************************************
 ** SHOT BY FOE 2
 *********************************************************************/

BulletDirected::BulletDirected()
{
    setDimensions(10,10);
    setBulletPix(QPixmap(":/images/images/enemybullet.png"));

    setMotion();
}

void BulletDirected::move()
{
    if(game->isPaused() == false){
        if(game->isInvincible() == false){
            QList<QGraphicsItem*> colliding_items = collidingItems();

            for(int i = 0, n = colliding_items.size(); i < n; ++i){
                if(typeid(*(colliding_items[i])) == typeid(Player)){
                    game->death();
                    deleteLater();
                    return;
                }
            }
        }


        double pythagorean = sqrt((getXTrajectory()*getXTrajectory())+(getYTrajectory()*getYTrajectory()));

        setPos(x()+(getXTrajectory())*getSpeed()/pythagorean,y()+(getYTrajectory())*getSpeed()/pythagorean);


        checkStatus();
    }
}
