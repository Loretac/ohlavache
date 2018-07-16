#include "enemy.h"
#include <QTimer>

#include "playerbullet.h"
#include "game.h"

extern Game * game;

/*********************************************************************
 **
 *********************************************************************/

void enemy::setEnemyPix(QPixmap map)
{
    enemyPix = new QGraphicsPixmapItem();
    enemyPix->setPixmap(map);
}

void enemy::setHealthPix(QPixmap map)
{
    healthPix = new QGraphicsPixmapItem();
    healthPix->setPixmap(map);
}

QGraphicsPixmapItem* enemy::getEnemyPix()
{
    return enemyPix;
}

QGraphicsPixmapItem* enemy::getHealthPix()
{
    return healthPix;
}

void enemy::setDimensions(int pixWidth, int pixHeight, int xOffset, int yOffset)
{
    width = pixWidth;
    height = pixHeight;
    hbX = xOffset;
    hbY = yOffset;
}

void enemy::setHealth(int val)
{
    health = val;
}

void enemy::setStartingHealth(int val)
{
    startingHealth = val;
    health = val;
}

int enemy::getHealth()
{
    return health;
}

int enemy::getStartingHealth()
{
    return startingHealth;
}

void enemy::positionHealth()
{
    healthPix->setPos(hbX,hbY);
}

int enemy::getWidth()
{
    return width;
}

int enemy::getHeight()
{
    return height;
}

int enemy::getHBX()
{
    return hbX;
}

int enemy::getHBY()
{
    return hbY;
}

bool enemy::isDead()
{
    return dead;
}

void enemy::setMotion()
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            this,SLOT(move()));

    timer->start(10);
}

void enemy::setSize(std::string val)
{
    size = val;

    if(val == "S"){
        barsize = S_BAR_SIZE;
    }
    else if(val == "M"){
        barsize = M_BAR_SIZE;
    }
}

bool enemy::getMoveLeft()
{
    return moveLeft;
}

void enemy::setMoveLeft(bool val)
{
    moveLeft = val;
}

void enemy::checkStatus()
{
    if(game->isPaused() == false && game->isInvincible() == false){
        QList<QGraphicsItem *> colliding_items = collidingItems();

        for(int i = 0, n = colliding_items.size(); i<n; ++i){
            if(typeid(*(colliding_items[i])) == typeid(Player)){

                damage();

                game->death();

                break;

            }
            else if(typeid(*(colliding_items[i])) == typeid(PlayerBullet)){

                damage();

                // Deleting bullet here is more convenient than in bullet class, since
                // there is one type of bullet but various enemy types.
                // Change the type, then delete.
                PlayerBullet *bullet = dynamic_cast<PlayerBullet*>(colliding_items[i]);
                bullet->deleteLater();

                break;

            }
        }
    }


    if(pos().y() > 600 ||
            pos().y() + height < -10 ||
            pos().x() > 800 ||
            pos().x() + width < 0 ||
            health <= 0){
        dead = true;
    }
}

void enemy::damage()
{
    health--;

    // save the current position before we make changes
    currXCoord = x();
    currYCoord = y();

    // hp is rounded to hearest int. Add 0.5 to account for truncating
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
    positionHealth();

    // no healthbar image if health is 0
    if(health > 0){
        // update the healthbar
        // Set image after offsetting; convert to QString
        healthPix->setPixmap(QPixmap(QString::fromStdString(healthbarImage)));
    }

    // set the position last
    this->setPos(currXCoord,currYCoord);
}
