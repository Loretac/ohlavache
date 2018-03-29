#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "bullet.h"
#include "enemy.h"

#include <QDebug>

/*********************************************************************
 ** Constructor. Sets the image of the player.
 *********************************************************************/
Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/jet.png"));
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
        if ( !event->isAutoRepeat() ){
            Bullet * bullet = new Bullet();
            bullet->setPos(x()+22,y()); // offset for character
            scene()->addItem(bullet); // add bullet to scene
        // play bulletsound?
        }
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

/*********************************************************************
 ** The movePlayer function operates on a timer in game.cpp.
 ** It continuously checks which keys are being pressed down and
 ** adjusts player movement accordingly.
 *********************************************************************/
void Player::movePlayer(){
    if(keyLeft && keyRight){
        // no x-axis movement
    }
    if (keyLeft && (pos().x() > 0)) {
        setPos(x()-5,y());
    }
    else if(keyRight && (pos().x() < 740)){
        setPos(x()+5,y());
    }

    if(keyUp && keyDown){
        // no y-axis movement
    }
    else if(keyUp && (pos().y() > 0)){
        setPos(x(),y()-5);
    }
    else if(keyDown && (pos().y() < 500)){
        setPos(x(),y()+5);
    }
}

/*********************************************************************
 ** Spawns enemies based on timer in game.cpp
 *********************************************************************/
void Player::spawn()
{
    // create an enemy
    Enemy *enemy = new Enemy();

    // add to the scene
    scene()->addItem(enemy);
}
