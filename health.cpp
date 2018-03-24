#include "health.h"
#include <QFont>




Health::Health(QGraphicsItem *parent)
{
    // initialize health to 3
    health = 3;

    // draw the text
    //convert to string...
    setPlainText(QString("Health: ") + QString::number(health));

    setDefaultTextColor(Qt::red); // make text blue
    setFont(QFont("times", 16)); // font family and size

}


void Health::decrease()
{
    // decrease the health
    health--;

    // update the text
    setPlainText(QString("Health: ") + QString::number(health));


}



int Health::getHealth()
{
    return health;
}
