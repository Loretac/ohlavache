#include "bulletsimple.h"

#include "game.h"

extern Game *game;

/*********************************************************************
 ** Bullet that moves in straight downward direction, shot by Level 1
 ** boss.
 *********************************************************************/

BulletSimple::BulletSimple()
{
    setDimensions(10,10);
    setBulletPix(QPixmap(":/images/images/enemybullet.png"));

    setMotion();
}

void BulletSimple::move()
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


        setPos(x(),y()+5);

        checkStatus();
    }
}
