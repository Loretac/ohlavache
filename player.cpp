#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "playerbullet.h"
//#include "enemytemp.h"
#include "game.h"

#include <QDebug>
#include <QTimer>

extern Game * game;

/*********************************************************************
 ** Player constructor. Sets the image of the player and connects
 ** to movement timer.
 *********************************************************************/
Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    //setPixmap(QPixmap(":/images/images/rocket.png"));

    setPixmap(playerPix);

    //setPixmap();
    width = 60;
    height = 82;

    //player movement
    movementTimer = new QTimer(this);
    QObject::connect(movementTimer,SIGNAL(timeout()),this,SLOT(movePlayer()));
    movementTimer->start(2);

    // player shooting
    shootingTimer = new QTimer(this);
    QObject::connect(shootingTimer,SIGNAL(timeout()),this,SLOT(shoot()));
    shootingTimer->start(350);

    connect(game,SIGNAL(dying()),
            this,SLOT(paralyzed()));
}

/*********************************************************************
 ** Takes the key being pressed, adds it to the list of bool
 ** member variables.
 *********************************************************************/
void Player::keyPressEvent(QKeyEvent *event){

    // check which key was pressed
    switch ( event->key() )
    {
    case Qt::Key_Left:
        keyLeft = true;
        break;
    case Qt::Key_Right:
        keyRight = true;
        break;
    case Qt::Key_Up:
        keyUp = true;
        break;
    case Qt::Key_Down:
        keyDown = true;
        break;
    case Qt::Key_Space:
    {
//        if ( !event->isAutoRepeat() ){
//            Bullet * bullet = new Bullet();
//            bullet->setPos(x()+22,y()); // offset for character
//            scene()->addItem(bullet); // add bullet to scene
//        // play bulletsound?
//        }
    }
        keySpace = true;
        break;
    case Qt::Key_Escape:
        exit(0);
    default:
        return;
    }
}

/*********************************************************************
 ** Checks if key is released. Removes key from list of bool
 ** variables.
 *********************************************************************/
void Player::keyReleaseEvent(QKeyEvent *event){
    if ( !event->isAutoRepeat() )
    {
        switch ( event->key() )
        {
        case Qt::Key_Left:
            keyLeft = false;
            break;
        case Qt::Key_Right:
            keyRight = false;
            break;
        case Qt::Key_Up:
            keyUp = false;
            break;
        case Qt::Key_Down:
            keyDown = false;
            break;
        case Qt::Key_Space:
            keySpace = false;
            break;
        default:
            return;
        }
    }
}

int Player::getwidth()
{
    return width;
}

int Player::getheight()
{
    return height;
}

/*********************************************************************
 ** The movePlayer function operates on a timer in player.cpp
 ** It continuously checks which keys are being pressed down and
 ** adjusts player movement accordingly.
 *********************************************************************/
void Player::movePlayer(){

    if(game->isPaused() == false){
        if(keyLeft && keyRight){
            // no x-axis movement
        }
        if (keyLeft && (pos().x() > 0)) {
            setPos(x()-6,y());
        }
        else if(keyRight && (pos().x() < 740)){
            setPos(x()+6,y());
        }

        if(keyUp && keyDown){
            // no y-axis movement
        }
        else if(keyUp && (pos().y() > 0)){
            setPos(x(),y()-6);
        }
        else if(keyDown && (pos().y() < 500)){
            setPos(x(),y()+6);
        }
    }
}

void Player::shoot()
{
    if(game->isPaused() == false){
        if(keySpace){
            PlayerBullet * bullet = new PlayerBullet();
            bullet->setPos(x()+26.5,y()); // offset for character
            scene()->addItem(bullet); // add bullet to scene
        }
    }
}

void Player::paralyzed()
{
    shootingTimer->stop();
    movementTimer->stop();
}

void Player::hideImage()
{
    setPixmap(QPixmap(":/images/images/transparent.png"));
}

void Player::showImage()
{
    setPixmap(playerPix);
}



