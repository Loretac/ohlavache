#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h> // rand -> really large int

// bullet constructor
Enemy::Enemy()
{
    // set random position


    int random_number = rand() % 700; // 100 less than width of screen so enemeis won't be cut off
    setPos(random_number,0);




    // draw the rect
    setRect(0,0,100,100);

    // connect to slot
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));

    // every 50 ms, timeout signal emitted and bullet moves
    timer->start(50);

}

void Enemy::move()
{
    // move the enemy down
    setPos(x(),y()+5);

    // delete the bullets
    if(pos().y() + rect().height() < 0){ // off the screen
        scene()->removeItem(this);
        delete this;
    }
}
