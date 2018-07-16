#include "playerbullet.h"
#include <QTimer>
#include <QList>

#include "game.h"

#include "enemy.h"


#include <QDebug>

#include <QGraphicsPixmapItem>

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
        // Bullet deletion upon collision with enemy occurs in enemy class.
        // If it occurred here instead, we'd have to check each type of enemy.

        // move the bullet up
        setPos(x(),y()-10);

        // delete the bullets after they leave the screen
        if(pos().y() + pixmap().height() < 0){ // off the screen
            deleteLater();
        }
    }
}
