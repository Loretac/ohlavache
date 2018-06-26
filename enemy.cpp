#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h> // rand -> really large int
#include "game.h"
#include "enemybullet.h"

#include <QGraphicsItemGroup>

#include <QDebug>

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

    // Create the pixmaps
    enemyPix = new QGraphicsPixmapItem();
    healthPix = new QGraphicsPixmapItem();

    if(type == 1){

        size = "S";
        barsize = S_BAR_SIZE;

        // Add the images
        enemyPix->setPixmap(QPixmap(":/images/images/ufo.png"));
        healthPix->setPixmap(QPixmap(":/images/images/Shb2.png")); // needs updating

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

    }
    else if(type == 2){

        size = "M";
        barsize = M_BAR_SIZE;

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
        timer->start(5);

        QTimer *bulletTimer = new QTimer();
        connect(
            bulletTimer,SIGNAL(timeout()),
            this, SLOT(shoot())
        );

        bulletTimer->start(500);
    }
    else if(type == 3){

        size = "S";
        barsize = S_BAR_SIZE;

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
        connect(timer,SIGNAL(timeout()),this, SLOT(move1()));

        // every 5 ms, timeout signal emitted and enemy moves
        timer->start(5);

        QTimer *bulletTimer = new QTimer();
        connect(
            bulletTimer,SIGNAL(timeout()),
            this, SLOT(shoot2())
        );

        bulletTimer->start(1500);
    }
}

/*********************************************************************
 ** Checks if enemy is colliding with player
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

    // save the current position before we make changes
    currXCoord = this->x();
    currYCoord = this->y();

    // update the healthbar
    delete healthPix;
    healthPix = new QGraphicsPixmapItem();
    this->addToGroup(healthPix);

    // hp is rounded to nearest int. Add 0.5 to account for truncating
    double hitpoints = (((float)barsize / startingHealth) * health) + 0.5;
    int hp = (int)hitpoints;

    // health bar will never show 0
    if(hp <= 0){
        hp = 1;
    }

    // create a std::string that holds the filename
    std::string healthbarImage = ":/images/images/" + size + "hb" + std::to_string(hp) + ".png";

    // which enemy type? to offset healthbar
    if(enemyType == 1){
        healthPix->setPos(10,-10);
    }
    else if(enemyType == 2){
        healthPix->setPos(0,-10);
    }
    else if(enemyType == 3){
        healthPix->setPos(10,-10);
    }

    // no healthbar image if health is 0
    if(health > 0){
        // Set image after offsetting; convert to QString
        healthPix->setPixmap(QPixmap(QString::fromStdString(healthbarImage)));
    }

    // set the position last
    this->setPos(currXCoord,currYCoord);

    return;
}

/*********************************************************************
 ** Shoots a bullet straight downwards
 *********************************************************************/
void Enemy::shoot()
{
    // create a bullet
    enemybullet *Bullet = new enemybullet(1);
    Bullet->setPos(x()+42,y()+84); // todo: offset for character!
    scene()->addItem(Bullet);
}

// this function runs once each time a bullet is created
void Enemy::shoot2()
{


    // create a bullet
    enemybullet *Bullet = new enemybullet(2);

    // coordinates of bullet's source
    int xSource = x()+50;
    int ySource = y()+27;

    // coordinates of center of player

    int xPlayer = game->player->x()+30;
    int yPlayer = game->player->y()+42;

    Bullet->getX(xPlayer-xSource);
    Bullet->getY(yPlayer-ySource);

    //qDebug() << xSource << " " << ySource << "    " << xPlayer << yPlayer;



    Bullet->setPos(xSource,ySource); // todo: offset for character!
    scene()->addItem(Bullet);
}

/*********************************************************************
 ** Movement for standard UFOs
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
        setPos(x(),y()+1.3);

        // if off the screen, delete the enemy
        if(pos().y() > 600){
            scene()->removeItem(this);
            delete this;
        }
    }
}

/*********************************************************************
 ** Movement for Level 1 boss
 *********************************************************************/
void Enemy::move2()
{
    if(game->paused == false){

        checkCollision();

        if(health <= 0){
            scene()->removeItem(this);
            emit boss1Dead(); // emits signal connected to slot in levels
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
