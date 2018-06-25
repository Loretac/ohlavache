#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h> // rand -> really large int
#include "game.h"
#include "enemybullet.h"

#include <QGraphicsItemGroup>

#include <string> // std::string, std::to_string

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
    startingHealth = hp;
    enemyType = type;

    if(type == 1){

        size = "S";

        // Create the pixmaps
        enemyPix = new QGraphicsPixmapItem();
        healthPix = new QGraphicsPixmapItem();

        // Add the images
        enemyPix->setPixmap(QPixmap(":/images/images/ufo.png"));
        healthPix->setPixmap(QPixmap(":/images/images/Shb2.png"));

        // add to the group
        this->addToGroup(enemyPix);
        this->addToGroup(healthPix);

        healthPix->setPos(10,-10);

        // assign a random position to enemy
        randomstart = rand()%700;
        //int random_number = rand() % 700; // 100 less than width of screen so enemies won't be cut off
        setPos(randomstart,-100); // set random position

        // connect to slot
        QTimer *timer = new QTimer();
        connect(
            timer,SIGNAL(timeout()),
            this, SLOT(move1())
        );

        // every 5 ms, timeout signal emitted and enemy moves
        timer->start(5);

//        QTimer *bulletTimer = new QTimer();
//        connect(
//            bulletTimer,SIGNAL(timeout()),
//            this, SLOT(shoot())
//        );

//        bulletTimer->start(1500);
    }
    else if(type == 2){

        size = "M";

        // Create the pixmaps
        enemyPix = new QGraphicsPixmapItem();
        healthPix = new QGraphicsPixmapItem();

        // Add the images
        enemyPix->setPixmap(QPixmap(":/images/images/johnny.png"));
        healthPix->setPixmap(QPixmap(":/images/images/Mhb4.png"));

        // add to the group
        this->addToGroup(enemyPix);
        this->addToGroup(healthPix);

        healthPix->setPos(0,-10);

        // assign a random position to enemy
        randomstart = rand()%700;
        //int random_number = rand() % 700; // 100 less than width of screen so enemies won't be cut off
        setPos(randomstart,-100); // set random position






        // connect to slot
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this, SLOT(move2()));

        // every 5 ms, timeout signal emitted and enemy moves
        timer->start(1);

        QTimer *bulletTimer = new QTimer();
        connect(
            bulletTimer,SIGNAL(timeout()),
            this, SLOT(shoot())
        );

        bulletTimer->start(500);
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

/*********************************************************************
 ** The damage function lowers the enemy's health and updates their
 ** health bar.
 *********************************************************************/
void Enemy::damage()
{
    health--;

    currXCoord = this->x();
    currYCoord = this->y();

    delete healthPix;
    healthPix = new QGraphicsPixmapItem();

    this->addToGroup(healthPix);

    // create a std::string that holds the filename
    std::string healthbarImage = ":/images/images/" + size + "hb" + std::to_string(health) + ".png";

    if(enemyType == 1){
        healthPix->setPos(10,-10);
    }
    else if(enemyType == 2){
        healthPix->setPos(0,-10);
    }

    // no healthbar image if health is 0
    if(health > 0){
        // convert std::string to QString, set as Pixmap
        healthPix->setPixmap(QPixmap(QString::fromStdString(healthbarImage)));
    }

    this->setPos(currXCoord,currYCoord);

    return;
}

/*********************************************************************
 ** Shoots a bullet straight downwards
 *********************************************************************/
void Enemy::shoot()
{
    // create a bullet
    enemybullet *Bullet = new enemybullet();
    Bullet->setPos(x()+42,y()+84); // todo: offset for character!
    scene()->addItem(Bullet);
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
            setPos(x()+10,y());
            moveLeft = false;
        }
        else if(((x() > 0 && moveLeft) || (x() >= 700 && !moveLeft))){
            // change direction
            setPos(x()-10, y());
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
