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
/*********************************************************************
 **
 *********************************************************************/
enemybullet::enemybullet(int bulletType)
{
    type = bulletType;

    if(type == 1){
        // create the bullet image
        QPixmap bulletMap(":/images/images/enemybullet.png");

        // create a resized copy
        width = 10;
        height = 10;
        QPixmap scaled = bulletMap.scaled(QSize(width,height));

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
        width = 10;
        height = 10;
        QPixmap scaled = bulletMap.scaled(QSize(width,height));

        setPixmap(scaled);

        // connect to slot
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),
                this, SLOT(move2()));

        timer->start(5);
    }
    else if(type == 3){
        // create the bullet image
        QPixmap bulletMap(":/images/images/timebomb.png");

        // create a resized copy
        width = 50;
        height = 50;
        QPixmap scaled = bulletMap.scaled(QSize(width,height));

        setPixmap(scaled);


        // connect to slot
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),
                this, SLOT(move3()));

        timer->start(5);
    }
    else if(type == 4){
        // create the bullet image
        QPixmap bulletMap(":/images/images/enemybullet.png");

        // create a resized copy
        width = 10;
        height = 10;
        QPixmap scaled = bulletMap.scaled(QSize(width,height));

        setPixmap(scaled);

        // connect to slot
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),
                this, SLOT(move2()));

        timer->start(5);
    }


}



/*********************************************************************
 **
 *********************************************************************/
void enemybullet::setXtrajectory(double X)
{
    xTrajectory = X;
}

/*********************************************************************
 **
 *********************************************************************/
void enemybullet::setYtrajectory(double Y)
{
    yTrajectory = Y;
}

void enemybullet::setSpeed(double newSpeed)
{
    speed = newSpeed;
}

int enemybullet::getwidth()
{
    return width;
}

int enemybullet::getheight()
{
    return height;
}



/*********************************************************************
 ** Move function for undirected bullets shot by Level 1 boss. These
 ** bullets travel straight downward.
 *********************************************************************/
void enemybullet::move()
{
    if(game->paused == false){

        QList<QGraphicsItem *> colliding_items = collidingItems();

        // Check if the bullet is colliding with the player
        for(int i = 0, n = colliding_items.size(); i < n; ++i){
            if(typeid(*(colliding_items[i])) == typeid(Player)){
                game->death();
                scene()->removeItem(this);
                delete this;
                return;
            }
         }

        // if not colliding with player, move downward
        setPos(x(),y()+5);

        // if off the bottom of screen, delete
        if(pos().y()  > 600){

            //qDebug() << "bullet deleted";
            scene()->removeItem(this);
            delete this;
        }
    }
}

/*********************************************************************
 ** Move function for directed bullets. Used by Level 2 minions and
 ** bullets from exploded bombs shot by Level 2 boss.
 **
 ** Although the function runs repeatedly to continuously update the
 ** position of the bullet, the x and y coordinates remain the same,
 ** so the bullet always travels in a straight line even if the enemy
 ** or player has moved.
 **
 ** xCoord and yCoord must be obtained before running this function
 ** (speed optional).
 *********************************************************************/
void enemybullet::move2()
{
    if(game->paused == false){

        QList<QGraphicsItem *> colliding_items = collidingItems();

        // Check if the bullet is colliding with the player
        for(int i = 0, n = colliding_items.size(); i < n; ++i){
            if(typeid(*(colliding_items[i])) == typeid(Player)){
                game->death();
                scene()->removeItem(this);
                delete this;
                return;
            }
         }

        // xCoord and yCoord obtained with getters in enemy function upon bullet creation

        // get pythagorean
        double pythagorean = sqrt((xTrajectory*xTrajectory)+(yTrajectory*yTrajectory));

        // if we don't divide by a factor of pythagorean, bullets starting farther
        // from the player will travel faster - not ideal...
        setPos(x()+(xTrajectory)*speed/pythagorean,y()+(yTrajectory)*speed/pythagorean);

        // if bullet is anywhere off the screen, delete it
        if(pos().y() > 600 ||
                pos().y()+pixmap().height() < -10 ||
                pos().x()  >800 ||
                pos().x() + pixmap().width() < 0 ){
            //qDebug() << pos().x() << " " <<  pos().y();
            scene()->removeItem(this);

            delete this;

        }
    }
}

// Trajectory for bombs shot by Level 2 boss.
void enemybullet::move3()
{
    if(game->paused == false){

        QList<QGraphicsItem *> colliding_items = collidingItems();

        // Check if the bullet is colliding with the player
        for(int i = 0, n = colliding_items.size(); i < n; ++i){
            if(typeid(*(colliding_items[i])) == typeid(Player)){
                emit collide();
                scene()->removeItem(this);
                game->death();
                delete this;
                return;
            }
         }

        // xCoord and yCoord obtained with getters in enemy function upon bullet creation

        // get pythagorean
        double pythagorean = sqrt((xTrajectory*xTrajectory)+(yTrajectory*yTrajectory));

        // if we don't divide by a factor of pythagorean, bullets starting farther
        // from the player will travel faster - not ideal...
        setPos(x()+(xTrajectory)/pythagorean*3,y()+(yTrajectory)/pythagorean*3);

        counter++;

        if(counter >= pythagorean / 3){
            emit arrived();
            scene()->removeItem(this);
            delete this;
            return;
        }

        // if bullet is anywhere off the screen, delete it
        if(pos().y() > 600 ||
                pos().y()+pixmap().height() < -10 ||
                pos().x()  >800 ||
                pos().x() + pixmap().width() < 0 ){
            //qDebug() << pos().x() << " " <<  pos().y();
            scene()->removeItem(this);

            emit arrived();

            delete this;

        }
    }
}
