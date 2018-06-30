#include "foe1.h"
#include "game.h"

#include <stdlib.h> // rand


#include <QTimer>

extern Game *game;

Foe1::Foe1()
{
    setStartingHealth(2);

    setEnemyPix(QPixmap(":/images/images/ufo.png"));
    setHealthPix(QPixmap(":/images/images/Shb2.png"));

    setSize("S");

    addToGroup(getEnemyPix());
    addToGroup(getHealthPix());

    setDimensions(100,53,10,-10);

    positionHealth();

    setPos(rand()% (800-getWidth()),-getHeight());

    setMotion();



}

void Foe1::move()
{
    if(game->isPaused() == false){

        setPos(x(),y()+1.3);

        checkStatus();

        if(isDead()){
            deleteLater();
        }

    }
}
