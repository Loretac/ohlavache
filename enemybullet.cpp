#include "enemybullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include "game.h"

#include <QGraphicsPixmapItem>

// include external global object called game
extern Game * game;

// enemy bullet constructor
enemybullet::enemybullet()
{
    // create the bullet image
    QPixmap bulletMap(":/images/images/enemybullet.png");

    // create a resized copy
    QPixmap scaled = bulletMap.scaled(QSize(10,10));

    setPixmap(scaled);

    // connect to slot
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),
            this, SLOT(move()));

    timer->start(5);
}



void enemybullet::move()
{
    if(game->paused == false){

        QList<QGraphicsItem *> colliding_items = collidingItems();

        for(int i = 0, n = colliding_items.size(); i < n; ++i){
            if(typeid(*(colliding_items[i])) == typeid(Player)){
                game->death();
                scene()->removeItem(this);
                delete this;
                return;
            }
         }

        setPos(x(),y()+5);

        if(pos().y() + pixmap().height() > 700){
            scene()->removeItem(this);
            delete this;
        }
    }
}
