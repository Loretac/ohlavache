#include "bulletminesmall.h"

#include "playerbullet.h"
#include "game.h"

#include <math.h>

extern Game *game;

/*********************************************************************
 ** Small mine (bomb that explodes on contact) shot by Level 4 foe
 *********************************************************************/

BulletMineSmall::BulletMineSmall()
{
    setDimensions(33,33);
    setBulletPix(QPixmap(":/images/images/mine.png"));

    setMotion();
}

void BulletMineSmall::move()
{
    if(game->isPaused() == false){
        if(game->isInvincible() == false){
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
        }


        double pythagorean = sqrt((getXTrajectory()*getXTrajectory())+(getYTrajectory()*getYTrajectory()));

        setPos(x()+(getXTrajectory())*getSpeed()/pythagorean,y()+(getYTrajectory())*getSpeed()/pythagorean);


        checkStatus();
    }
}
