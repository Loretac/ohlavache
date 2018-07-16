#include "laser.h"
#include "game.h"

#include <math.h> // for arc tan

#include <QTimer>

#include <QDebug>

extern Game *game;

/*********************************************************************
 ** Laser shot by Level 4 boss(es)
 *********************************************************************/

Laser::Laser()
{
    setPixmap(QPixmap(":/images/images/laser.png"));


    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            this,SLOT(move()));
    timer->start(5);

    setTransformOriginPoint(0,5);
}

void Laser::move()
{
    if(game->isPaused() == false){
        QList<QGraphicsItem *> colliding_items = collidingItems();

        for(int i = 0, n = colliding_items.size(); i<n; ++i){
            if(typeid(*(colliding_items[i])) == typeid(Player)){

                // contact with player
                game->death();
                break;

            }
        }
    }
}
