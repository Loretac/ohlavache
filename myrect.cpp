#include "myrect.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "bullet.h"


void MyRect::keyPressEvent(QKeyEvent *event){
    // check what key was pressed
    if(event->key() == Qt::Key_Left){
        setPos(x()-10,y());
    }
    else if(event->key() == Qt::Key_Right){
        setPos(x()+10,y());
    }
    else if(event->key() == Qt::Key_Up){
        setPos(x(),y()-10);
    }
    else if(event->key() == Qt::Key_Down){
        setPos(x(),y()+10);
    }
    else if(event->key() == Qt::Key_Space){
        // create a bullet
        Bullet *bullet = new Bullet();
        bullet->setPos(x(),y());

        // add the bullet to the scene
        scene()->addItem(bullet);
    }
}
