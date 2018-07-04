#include "playerbullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
//#include "enemytemp.h"
#include "game.h"

#include "enemy.h"

#include "foe1.h"

#include <QDebug>

#include <QGraphicsPixmapItem>

// there is an external global object called game, so we can increase score
// score is part of the game class.
extern Game * game;

/*********************************************************************
 ** Bullet constructor. Bullets are created each time the player
 ** shoots. This constructor draws the bullet and connects it to the
 ** move function.
 *********************************************************************/
PlayerBullet::PlayerBullet()
{
    // draw the bullet
    setPixmap(QPixmap(":/images/images/bullet.png"));
    width = 7;
    height=25;

    // move the bullet:

    // connect to slot
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));

    // every 5 ms, timeout signal emitted and bullet moves
    timer->start(5);

}

int PlayerBullet::getwidth()
{
    return width;
}

int PlayerBullet::getheight()
{
    return height;
}

/*********************************************************************
 ** This function moves the player's bullet towards the enemies.
 ** It runs on a timer in the Bullet constructor above.
 *********************************************************************/
void PlayerBullet::move()
{
    if(game->isPaused() == false){

//        QList<QGraphicsItem *> colliding_items = collidingItems();
//        // collidingItems() member function returns list of pointers to all the QGraphics items
//        // that the bullet is colliding with

//        //traverse to see if bullet is colliding with enemy
//        for(int i = 0, n = colliding_items.size(); i < n; ++i){
//            if(typeid(*(colliding_items[i])) == typeid(Foe1)){
//                //qDebug() << "bullet";
//               // increase the score
//               //game->score->increase();

//               // typecast from QGraphicsItem* to Enemy*
//               Foe1 *enemy = dynamic_cast<Foe1 *>(colliding_items[i]);
//               enemy->damage(); // Call damage function on enemy

//                // remove the bullet from the scene
//               deleteLater();
//                //scene()->removeItem(this);

//                //then, delete the bullet
//                //delete this;

//                // exit
//                return;
//            }
//        }

        // move the bullet up
        setPos(x(),y()-10);

        // delete the bullets after they leave the screen
        if(pos().y() + pixmap().height() < 0){ // off the screen
            deleteLater();
        }
    }
}
