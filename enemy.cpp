#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h> // rand -> really large int
#include "game.h"
#include "enemybullet.h"

#include "target.h"

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

    if(type == 1){ // LEVEL 1 MINIONS

        size = "S";
        barsize = S_BAR_SIZE;

        // Add the images
        enemyPix->setPixmap(QPixmap(":/images/images/ufo.png"));
        healthPix->setPixmap(QPixmap(":/images/images/Shb2.png")); // needs updating

        width = 100;
        height = 53;

        hbX = 10;
        hbY = -10;

        // add to the group
        this->addToGroup(enemyPix);
        this->addToGroup(healthPix);

        healthPix->setPos(hbX,hbY);

        // assign a random position to enemy
        int randomstart = rand()%700;
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
    else if(type == 2){ // LEVEL 1 BOSS

        size = "M";
        barsize = M_BAR_SIZE;

        // Add the images
        enemyPix->setPixmap(QPixmap(":/images/images/johnny.png"));
        healthPix->setPixmap(QPixmap(":/images/images/Mhb4.png"));

        width = 110;
        height = 114;

        hbX = 0;
        hbY = -10;

        // add to the group
        this->addToGroup(enemyPix);
        this->addToGroup(healthPix);

        healthPix->setPos(hbX,hbY);

        // assign a random position to enemy
        int randomstart = rand()%700;
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
            this, SLOT(boss1Shoot())
        );

        bulletTimer->start(500);
    }
    else if(type == 3){ // LEVEL 2 MINIONS

        size = "S";
        barsize = S_BAR_SIZE;

        // Add the images
        enemyPix->setPixmap(QPixmap(":/images/images/ufo.png"));
        healthPix->setPixmap(QPixmap(":/images/images/Shb2.png"));

        width = 100;
        height = 53;

        hbX = 10;
        hbY = -10;

        // add to the group
        this->addToGroup(enemyPix);
        this->addToGroup(healthPix);

        healthPix->setPos(hbX,hbY);

        // assign a random position to enemy
        int randomstart = rand()%700;
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
    else if(type == 4){ // LEVEL 2 BOSS
        size = "M";
        barsize = M_BAR_SIZE;

        // Add the images
        enemyPix->setPixmap(QPixmap(":/images/images/johnny.png"));
        healthPix->setPixmap(QPixmap(":/images/images/Mhb4.png"));

        width = 110;
        height = 114;

        hbX = 0;
        hbY = -10;

        // add to the group
        this->addToGroup(enemyPix);
        this->addToGroup(healthPix);

        healthPix->setPos(hbX,hbY);

        // assign a random position to enemy
        int randomstart = rand()%700;
        //int random_number = rand() % 700; // 100 less than width of screen so enemies won't be cut off
        setPos(randomstart,-100); // set random position

        // connect to slot
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this, SLOT(move4()));

        // every 5 ms, timeout signal emitted and enemy moves
        timer->start(5);

        QTimer *bulletTimer = new QTimer();
        connect(
            bulletTimer,SIGNAL(timeout()),
            this, SLOT(boss2Shoot())
        );

        bulletTimer->start(2500);
    }
    else if(type == 5){ // LEVEL 3 MINIONS

        size = "S";
        barsize = S_BAR_SIZE;

        // Add the images
        enemyPix->setPixmap(QPixmap(":/images/images/ufo.png"));
        healthPix->setPixmap(QPixmap(":/images/images/Shb2.png"));

        width = 100;
        height = 53;

        hbX = 10;
        hbY = -10;

        // add to the group
        this->addToGroup(enemyPix);
        this->addToGroup(healthPix);

        healthPix->setPos(hbX,hbY);

        // assign a random position to enemy
        int randomstart = rand()%700; // 100 less than width of screen so enemies won't be cut off
        setPos(randomstart,-100); // set random position

        // connect to slot
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this, SLOT(move1()));

        // every 5 ms, timeout signal emitted and enemy moves
        timer->start(5);

        QTimer *bulletTimer = new QTimer();
        connect(
            bulletTimer,SIGNAL(timeout()),
            this, SLOT(shoot3M())
        );

        bulletTimer->start(2500);
    }
    else if(type == 6){
        size = "M";
        barsize = M_BAR_SIZE;

        // Add the images
        enemyPix->setPixmap(QPixmap(":/images/images/johnny.png"));
        healthPix->setPixmap(QPixmap(":/images/images/Mhb4.png"));

        width = 110;
        height = 114;

        hbX = 0;
        hbY = -10;

        // add to the group
        this->addToGroup(enemyPix);
        this->addToGroup(healthPix);

        healthPix->setPos(hbX,hbY);

        // assign a random position to enemy
        int randomstart = rand()%700;
        //int random_number = rand() % 700; // 100 less than width of screen so enemies won't be cut off
        setPos(randomstart,-100); // set random position

        // connect to slot
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this, SLOT(move6()));

        timer->start(5);

        QTimer *bulletTimer = new QTimer();
        connect(
            bulletTimer,SIGNAL(timeout()),
            this, SLOT(boss1Shoot())
        );

        bulletTimer->start(500);

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
    double rawHP = (((float)barsize / startingHealth) * health) + 0.5;

    // roundedHP is amount shown in health bar
    int roundedHP = (int)rawHP;

    // health bar will never show 0
    if(roundedHP <= 0){
        roundedHP = 1;
    }

    // create a std::string that holds the filename
    std::string healthbarImage = ":/images/images/" + size + "hb" + std::to_string(roundedHP) + ".png";

    // set position of health bar
    healthPix->setPos(hbX,hbY);

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
 ** Function for Level 1 Boss shooting
 *********************************************************************/
void Enemy::boss1Shoot()
{
    // create a bullet
    enemybullet *Bullet = new enemybullet(2);

    Bullet->setXtrajectory(0);
    Bullet->setYtrajectory(1);
    Bullet->setSpeed(8);
    Bullet->setPos(x()+width/2,y()+height/2); // todo: offset for character!
    scene()->addItem(Bullet);
}

void Enemy::boss2Shoot()
{
    // create a bullet
    enemybullet *Bullet = new enemybullet(3);

    // coordinates of origin of bullet
    int xSource = x() + width/2 - Bullet->getwidth()/2;
    int ySource = y() + height/2 - Bullet->getheight()/2;

    // coordinates of center of player
    int xPlayer = game->getPlayerXPos() + game->getPlayerWidth()/2 - Bullet->getwidth()/2;
    int yPlayer = game->getPlayerYPos() + game->getPlayerHeight()/2 - Bullet->getheight()/2;

    // set the trajectory of the bullet
    Bullet->setXtrajectory(xPlayer-xSource);
    Bullet->setYtrajectory(yPlayer-ySource);

    // bullet starts at source we found earlier
    Bullet->setPos(xSource,ySource);

    // add a target
    target *newTarget = new target(1);

    scene()->addItem(newTarget);

    // when the bullet arrives, destroy the target
    connect( Bullet, SIGNAL(arrived()),
              newTarget, SLOT(boom())  );
    connect( Bullet, SIGNAL(collide()),
             newTarget, SLOT(deleteTarget()));


    scene()->addItem(Bullet);
}

void Enemy::boss3Shoot()
{

}

/*********************************************************************
 ** Function for Level 2 minion shooting. The function is run once
 ** each time a bullet is created. Bullets are directed along the
 ** path from the bullet's source to the player's position at the time
 ** of firing. The coordinates are passed through the getter functions
 ** of the enemybullet class.
 *********************************************************************/
void Enemy::shoot2()
{
    // create a bullet
    enemybullet *Bullet = new enemybullet(2);

    Bullet->setSpeed(3);

    // coordinates of bullet's source
    int xSource = x()+width/2;
    int ySource = y()+height/2;

    // coordinates of center of player
    int xPlayer = game->getPlayerXPos() + game->getPlayerWidth()/2 - Bullet->getwidth()/2;
    int yPlayer = game->getPlayerYPos() + game->getPlayerHeight()/2 - Bullet->getheight()/2;

    Bullet->setXtrajectory(xPlayer-xSource);
    Bullet->setYtrajectory(yPlayer-ySource);

    Bullet->setPos(xSource,ySource);
    scene()->addItem(Bullet);
}

// shooting for level 3 minions
void Enemy::shoot3M()
{
    // create a bullet
    enemybullet *Bullet = new enemybullet(3);

    // coordinates of origin of bullet
    int xSource = x() + width/2 - Bullet->getwidth()/2;
    int ySource = y() + height/2 - Bullet->getheight()/2;

    // coordinates of center of player
    int xPlayer = game->getPlayerXPos() + game->getPlayerWidth()/2 - Bullet->getwidth()/2;
    int yPlayer = game->getPlayerYPos() + game->getPlayerHeight()/2 - Bullet->getheight()/2;

    // set the trajectory of the bullet
    Bullet->setXtrajectory(xPlayer-xSource);
    Bullet->setYtrajectory(yPlayer-ySource);

    // bullet starts at source we found earlier
    Bullet->setPos(xSource,ySource);

    // add a target
    target *newTarget = new target(2);

    scene()->addItem(newTarget);

    // when the bullet arrives, destroy the target
    connect( Bullet, SIGNAL(arrived()),
              newTarget, SLOT(smallBoom())  );
    connect( Bullet, SIGNAL(collide()),
             newTarget, SLOT(deleteTarget()));


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
            return;
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
 ** Movement for Level 1/2? boss
 *********************************************************************/
void Enemy::move2()
{
    if(game->paused == false){

        checkCollision();

        if(health <= 0){
            scene()->removeItem(this);
            emit boss1Dead(); // emits signal connected to slot in levels
            delete this;
            return;
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

void Enemy::move4()
{
    if(game->paused == false){

        checkCollision();

        if(health <= 0){
            scene()->removeItem(this);
            emit boss2Dead(); // emits signal connected to slot in levels
            delete this;
            return;
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

void Enemy::move5()
{
    if(game->paused == false){

        // check if player colliding with enemy
        checkCollision();

        if(health <= 0){
            scene()->removeItem(this);
            delete this;
            return;
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

void Enemy::move6()
{
    if(game->paused == false){

        // check if player colliding with enemy
        checkCollision();

        if(health <= 0){
            scene()->removeItem(this);
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
