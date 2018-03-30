#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h> // rand -> really large int
#include "game.h"

extern Game * game; // there is an external global object called game
// used to decrease health after enemy crosses screen

// enemy constructor
Enemy::Enemy()
{
    // set random position


    int random_number = rand() % 700; // 100 less than width of screen so enemies won't be cut off
    setPos(random_number,0);




    // draw the rect
    setPixmap(QPixmap(":/images/ufo.png"));



    // connect to slot
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));

    // every 50 ms, timeout signal emitted and enemy moves
    timer->start(5);

}

void Enemy::move()
{
    if(game->paused == false){

            // before moving enemy, check if colliding with player
            // if enemy collides with player, destroy enemy and decrease health/lives
            QList<QGraphicsItem *> colliding_items = collidingItems();
            // collidingItems() member function returns list of pointers to all the QGraphics items
            // that the enemy is colliding with

            //traverse to see if enemy is colliding with player
            for(int i = 0, n = colliding_items.size(); i < n; ++i){
                if(typeid(*(colliding_items[i])) == typeid(Player)){
                   // increase the score
                   game->health->decrease();



                    // remove them both
                    //scene()->removeItem((colliding_items[i]));
                    scene()->removeItem(this); // remove the enemy

                    //then, delete them both
                    //delete colliding_items[i];
                    delete this;

                    // exit
                    return;
                }
            }













            // move the enemy down
            setPos(x(),y()+2);

            // delete the enemies and decrease score
            if(pos().y() > 600){ // off the screen
                // decrease the health
                game->health->decrease();

                scene()->removeItem(this);
                delete this;
            }

    }



}
