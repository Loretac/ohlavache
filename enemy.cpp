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
Enemy::Enemy(int type, int hp)
{
    health = hp;

    if(type == 1){
        int random_number = rand() % 700; // 100 less than width of screen so enemies won't be cut off
        setPos(random_number,-100); // set random position

        // draw the enemy
        setPixmap(QPixmap(":/images/ufo.png"));

        // connect to slot
        QTimer *timer = new QTimer();
        connect(
            timer,SIGNAL(timeout()),
            this, SLOT(move1())
        );

        // every 5 ms, timeout signal emitted and enemy moves
        timer->start(5);
    }
    else if(type == 2){
        int random_number = rand() % 700; // 100 less than width of screen so enemies won't be cut off
        setPos(random_number,-100); // set random position

        // draw the enemy
        QPixmap bgPixmap(":/images/boss1.png");

        // created a resized copy
        QPixmap scaled = bgPixmap.scaled(QSize(84,84));

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
 ** Checks if colliding with player
 *********************************************************************/
void Enemy::checkCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    // collidingItems() member function returns list of pointers to all the QGraphics items
    // that the enemy is colliding with

    for(int i = 0, n = colliding_items.size(); i < n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(Player)){

            // decrease enemy's health
            damage();

            // death of player
            game->death();

            // exit
            return;
        }
    }
}

void Enemy::damage()
{
    health--;
    return;
}

/*********************************************************************
 ** This function moves the enemy.
 *********************************************************************/
void Enemy::move1()
{
    if(game->paused == false){

        // check if player colliding with enemy
        checkCollision();

        if(health <= 0){
            scene()->removeItem(this);
            delete this;
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

// boss for level 1
void Enemy::move2()
{
    if(game->paused == false){

        checkCollision();

        if(health <= 0){
            scene()->removeItem(this);
            emit bossDead(); // emits signal connected to slot in levels
            delete this;
        }

        // if not colliding with player:

        // move the enemy down...
        if(y() < 10){
            setPos(x(),y()+2);
        }

        if(((x() < 700 && !moveLeft) || (x() <= 0 && moveLeft))){
            // change direction
            setPos(x()+11,y());
            moveLeft = false;
        }
        else if(((x() > 0 && moveLeft) || (x() >= 700 && !moveLeft))){
            // change direction
            setPos(x()-11, y());
            // set moveLeft
            moveLeft = true;
        }


        // if off the screen, delete the enemy
        if(pos().y() > 600){
            scene()->removeItem(this);
            delete this;
        }
    }
}
