#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "enemy.h"
#include "game.h"

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
Bullet::Bullet()
{
    // draw the bullet
    setPixmap(QPixmap(":/images/images/bullet.png"));

    // move the bullet:

    // connect to slot
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));

    // every 5 ms, timeout signal emitted and bullet moves
    timer->start(5);

}

/*********************************************************************
 ** This function moves the player's bullet towards the enemies.
 ** It runs on a timer in the Bullet constructor above.
 *********************************************************************/
void Bullet::move()
{
    if(game->paused == false){
        // before moving bullet, check if colliding with enemy
        // if bullet collides with enemy, destroy both
        QList<QGraphicsItem *> colliding_items = collidingItems();
        // collidingItems() member function returns list of pointers to all the QGraphics items
        // that the bullet is colliding with

        //traverse to see if bullet is colliding with enemy
        for(int i = 0, n = colliding_items.size(); i < n; ++i){
            if(typeid(*(colliding_items[i])) == typeid(Enemy)){
               // increase the score
               game->score->increase();

               // typecast from QGraphicsItem* to Enemy*
               Enemy *enemy = dynamic_cast<Enemy *>(colliding_items[i]);
               enemy->damage(); // Call damage function on enemy

                // remove the bullet from the scene
                scene()->removeItem(this);

                //then, delete the bullet
                delete this;

                // exit
                return;
            }
        }

        // move the bullet up
        setPos(x(),y()-5);

        // delete the bullets after they leave the screen
        if(pos().y() + pixmap().height() < 0){ // off the screen
            scene()->removeItem(this);
            delete this;
        }
    }
}
