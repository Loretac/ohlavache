#include "bulletsimple.h"

extern Game *game;

BulletSimple::BulletSimple()
{
    setDimensions(10,10);
    setBulletPix(QPixmap(":/images/images/enemybullet.png"));

    setMotion();
}

void BulletSimple::move()
{
    if(game->isPaused() == false){
        QList<QGraphicsItem*> colliding_items = collidingItems();

        for(int i = 0, n = colliding_items.size(); i < n; ++i){
            if(typeid(*(colliding_items[i])) == typeid(Player)){
                game->death();
                deleteLater();
                return;
            }
        }

        setPos(x(),y()+5);

        checkStatus();
    }
}
