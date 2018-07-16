#include "foe1.h"
#include "game.h"

#include <stdlib.h> // rand


#include <QTimer>

extern Game *game;

/*********************************************************************
 **
 *********************************************************************/

Foe1::Foe1()
{
    setStartingHealth(2);

    setDimensions(100,53,10,-10); // for ufo 1
    setEnemyPix(QPixmap(":/images/images/ufo.png"));

    setHealthPix(QPixmap(":/images/images/Shb2.png"));

    setSize("S");

    addToGroup(getEnemyPix());
    addToGroup(getHealthPix());



    positionHealth();

    setPos(rand()% (800-getWidth()),-getHeight());

    setMotion();

}

void Foe1::move()
{
    if(game->isPaused() == false){

        setPos(x(),y()+1);

        checkStatus();

        if(isDead()){
            deleteLater();
        }

    }
}
