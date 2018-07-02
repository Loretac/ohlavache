#include "bulletminesmall.h"

#include "playerbullet.h"

#include <math.h>

extern Game *game;

BulletMineSmall::BulletMineSmall()
{
    setDimensions(30,30);
    setBulletPix(QPixmap(":/images/images/enemybullet.png"));

    setMotion();
}

void BulletMineSmall::move()
{
    if(game->isPaused() == false){
        QList<QGraphicsItem*> colliding_items = collidingItems();
        // if bullet collides with player:
        // Explosion, Death, function returns
        for(int i = 0, n = colliding_items.size(); i < n; ++i){
            if(typeid(*(colliding_items[i])) == typeid(Player)){
                game->explosion1(game->getPlayerXPos(), game->getPlayerYPos());

                game->death();
                deleteLater();
                return;
            }
            else if(typeid(*(colliding_items[i])) == typeid(PlayerBullet)){
                game->explosion1(x(), y());
                deleteLater();
                return;
            }
        }

        double pythagorean = sqrt((getXTrajectory()*getXTrajectory())+(getYTrajectory()*getYTrajectory()));

        setPos(x()+(getXTrajectory())*getSpeed()/pythagorean,y()+(getYTrajectory())*getSpeed()/pythagorean);


        checkStatus();
    }
}
