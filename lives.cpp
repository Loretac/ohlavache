#include "lives.h"


/*********************************************************************
 ** The lives constructor sets the image of a "life". Display of
 ** lives is handled by game.cpp.
 *********************************************************************/
Lives::Lives(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/images/life.png"));

}

