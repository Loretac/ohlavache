#include "enemybullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include "game.h"

#include <math.h> // for sqrt

#include <QDebug>

#include <QGraphicsPixmapItem>

// include external global object called game
extern Game * game;

// enemy bullet constructor
enemybullet::enemybullet(int bulletType)
{
    type = bulletType;

    if(type == 1){
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
    else if(type == 2){
        // create the bullet image
        QPixmap bulletMap(":/images/images/enemybullet.png");

        // create a resized copy
        QPixmap scaled = bulletMap.scaled(QSize(10,10));

        setPixmap(scaled);

        // connect to slot
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),
                this, SLOT(move2()));

        timer->start(5);
    }


}

void enemybullet::getX(int X)
{
    xCoord = X;
}

void enemybullet::getY(int Y)
{
    yCoord = Y;
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

// this function runs constantly to determine the trajectory of the bullet
void enemybullet::move2()
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


        // xCoord and yCoord obtained with getters in enemy function

        // get pythagorean
        double pythagorean = sqrt((xCoord*xCoord)+(yCoord*yCoord));

        setPos(x()+(xCoord)/pythagorean*3,y()+(yCoord)/pythagorean*3);

        if(pos().y() + pixmap().height() > 700 ||
                pos().y()-pixmap().height() < -10 ||
                pos().x() + pixmap().width() >800 ||
                pos().x() - pixmap().width() < -10 ){
            scene()->removeItem(this);
            delete this;
        }
    }
}
