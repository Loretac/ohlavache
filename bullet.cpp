#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>

// bullet constructor
Bullet::Bullet()
{
    // draw the rect
    setRect(0,0,10,50);

    // connect to slot
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));

    // every 50 ms, timeout signal emitted and bullet moves
    timer->start(50);

}

void Bullet::move()
{
    // move the bullet up
    setPos(x(),y()-10);

    if(pos().y() + rect().height() < 0){ // off the screen
        scene()->removeItem(this);
        delete this;
    }
}
