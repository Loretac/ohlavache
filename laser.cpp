#include "laser.h"
#include "game.h"

#include <math.h> // for arc tan

#include <QTimer>

#include <QDebug>

extern Game *game;

Laser::Laser()
{
    setPixmap(QPixmap(":/images/images/laser.png"));

    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),
            this,SLOT(move()));
    timer->start(5);

    setTransformOriginPoint(0,5);
}

//void Laser::setSourceX(double val)
//{
//    sourceX = val;
//}

//void Laser::setSourceY(double val)
//{
//    sourceY = val;
//}

//void Laser::setTargetX(double val)
//{
//    targetX = val;
//}

//void Laser::setTargetY(double val)
//{
//    targetY = val;
//}

void Laser::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for(int i = 0, n = colliding_items.size(); i<n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(Player)){


            //qDebug() << "contact";
            //game->death();

            break;

        }
    }

}
