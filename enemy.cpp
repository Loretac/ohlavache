#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h> // rand -> really large int
#include "game.h"

extern Game * game; // there is an external global object called game
// used to decrease health after enemy crosses screen
// or end game


/*********************************************************************
 ** The enemy constructor is called each time spawn() in game.cpp
 ** is called.
 *********************************************************************/
Enemy::Enemy(int type)
{
    if(type == 1){
        int random_number = rand() % 700; // 100 less than width of screen so enemies won't be cut off
        setPos(random_number,-100); // set random position

        // draw the enemy
        setPixmap(QPixmap(":/images/ufo.png"));

        // connect to slot
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this, SLOT(move1()));

        // every 5 ms, timeout signal emitted and enemy moves
        timer->start(5);
    }
    else if(type == 2){
        int random_number = rand() % 700; // 100 less than width of screen so enemies won't be cut off
        setPos(random_number,-100); // set random position

        // draw the enemy
        QPixmap bgPixmap(":/images/boss1.png");

        // created a resized copy
        QPixmap scaled = bgPixmap.scaled(QSize(164,164));

        // set to the resized object
        setPixmap(scaled);

        // connect to slot
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this, SLOT(move2()));

        // every 5 ms, timeout signal emitted and enemy moves
        timer->start(5);
    }

}

/*********************************************************************
 ** This function moves the enemy.
 *********************************************************************/
void Enemy::move1()
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
                    // remove and delete the enemy
                    scene()->removeItem(this);
                    delete this;

                    // call game death function
                    game->death();

                    // exit
                    return;
                }
            }

            // if not colliding with player:

            // move the enemy down
            setPos(x(),y()+2);

            // if off the screen, delete the enemy
            if(pos().y() > 600){
                scene()->removeItem(this);
                delete this;
            }
    }
}

void Enemy::move2()
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
                    // remove and delete the enemy
                    scene()->removeItem(this);
                    delete this;

                    // call game death function
                    game->death();

                    // exit
                    return;
                }
            }

            // if not colliding with player:

            // move the enemy down
            if(x() < 700 && !moveLeft){
                setPos(x()+11,y()+2);
            }
            else if(x() >= 700 && !moveLeft){
                // change direction
                setPos(x()-11, y()+2);
                // set moveLeft
                moveLeft = true;
            }
            else if(x() > 0 && moveLeft){
                setPos(x()-11, y()+2);
            }
            else if(x() <= 0 && moveLeft){
                // change direction
                setPos(x()+11,y()+2);
                moveLeft = false;
            }


//            if(x() < 10 && moveLeft){
//                moveLeft = false;
//            }


            // if off the screen, delete the enemy
            if(pos().y() > 600){
                scene()->removeItem(this);
                delete this;
            }
    }
}
