#include "bulletminelarge.h"
#include "playerbullet.h"
#include "game.h"

extern Game *game;



/*********************************************************************
 ** Large mine (bomb that explodes on contact) shot by Level 3 boss
 *********************************************************************/

BulletMineLarge::BulletMineLarge()
{
    setDimensions(45,45);
    setBulletPix(QPixmap(":/images/images/mine.png"));

    setMotion();
}

void BulletMineLarge::move()
{
    if(game->isPaused() == false){
        if(game->isInvincible() == false){
            QList<QGraphicsItem*> colliding_items = collidingItems();

            for(int i = 0, n = colliding_items.size(); i < n; ++i){
                if(typeid(*(colliding_items[i])) == typeid(Player)){

                    game->explosion3(game->getPlayerXPos(), game->getPlayerYPos());

                    game->death();
                    deleteLater();
                    return;
                }
                else if(typeid(*(colliding_items[i])) == typeid(PlayerBullet)){
                    game->explosion3(x(), y());
                    deleteLater();
                    return;
                }
            }
        }


        setPos(x(),y()+5);

        checkStatus();
    }
}
