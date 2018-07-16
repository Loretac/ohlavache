#include "target.h"
#include "game.h"

extern Game * game;

target::target(int size)
{

    xCoord = game->getPlayerXPos()+5;
    yCoord = game->getPlayerYPos()+20;

    if(size == 1){
        setPixmap(QPixmap(":/images/images/target.png"));
    }
    else if(size == 2){
        // create the target image
        QPixmap targetMap(":/images/images/target.png");

        // create a resized copy
        width = 50;
        height = 50;
        QPixmap scaled = targetMap.scaled(QSize(width,height));

        setPixmap(scaled);
    }
    else if(size == 3){
        // create target image
        setPixmap(QPixmap(":/images/images/lasertarget.png"));
        height = 100;
        width = 100;
    }

    setZValue(-1); // so it is below the player

    this->setPos(xCoord,yCoord);

}

int target::getWidth()
{
    return width;
}

int target::getHeight()
{
    return height;
}

// The explosion/collision functions actually happen in the game class
// because the target is deleted right when the explosion happens.

// large bomb reaching destination
void target::boom()
{
    game->explosion1(xCoord, yCoord );
    deleteLater();
    return;
}

// small bomb reaching destination
void target::smallBoom()
{
    game->explosion2(xCoord,yCoord);
    deleteLater();
    return;
}

// large bomb colliding with player
void target::collision()
{
    game->explosion1(game->getPlayerXPos(), game->getPlayerYPos());
    deleteLater();
    return;
}

// small bomb colliding with player
void target::smallCollision()
{
    game->explosion2(game->getPlayerXPos(),game->getPlayerYPos());
    deleteLater();
    return;
}
