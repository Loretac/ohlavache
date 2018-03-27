#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "bullet.h"
#include "enemy.h"


Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/jet.png"));
    //QPixmap::scaled()
    //QPixmap::scaledToWidth(100,Qt::FastTransformation);

}

void Player::keyPressEvent(QKeyEvent *event){
    // check what key was pressed
    if(event->key() == Qt::Key_Left){
        if(pos().x() > 0){
            setPos(x()-40,y());
        }
    }
    else if(event->key() == Qt::Key_Right){
        if(pos().x() +100 < 800){
            setPos(x()+40,y());
        }
    }
    else if(event->key() == Qt::Key_Up){
        if(pos().y() > 0){
            setPos(x(),y()-40);
        }

    }
    else if(event->key() == Qt::Key_Down){
        if(pos().y() +100 < 600){
            setPos(x(),y()+40);
        }

    }
    else if(event->key() == Qt::Key_Space){
        // create a bullet
        Bullet *bullet = new Bullet();
        bullet->setPos(x()+22,y());

        // add the bullet to the scene
        scene()->addItem(bullet);
    }
}



void Player::spawn()
{
    // create an enemy
    Enemy *enemy = new Enemy();

    // add to the scene
    scene()->addItem(enemy);
}
