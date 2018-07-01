#include "bulletminelarge.h"


#include "playerbullet.h"

extern Game *game;

BulletMineLarge::BulletMineLarge()
{
    setDimensions(40,40);
    setBulletPix(QPixmap(":/images/images/enemybullet.png"));

    setMotion();
}

void BulletMineLarge::move()
{
    if(game->isPaused() == false){
        QList<QGraphicsItem*> colliding_items = collidingItems();

        for(int i = 0, n = colliding_items.size(); i < n; ++i){
            if(typeid(*(colliding_items[i])) == typeid(Player)){

                game->explosion1(game->getPlayerXPos(), game->getPlayerYPos());

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

        setPos(x(),y()+5);

        checkStatus();
    }
}
