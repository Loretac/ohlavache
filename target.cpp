#include "target.h"
#include "game.h"

extern Game * game;

target::target(int size)
{

    xCoord = game->player->x()+5;
    yCoord = game->player->y()+20;

    if(size == 1){
        setPixmap(QPixmap(":/images/images/target.png"));
    }
    else if(size == 2){
        // create the bullet image
        QPixmap targetMap(":/images/images/target.png");

        // create a resized copy
        width = 50;
        height = 50;
        QPixmap scaled = targetMap.scaled(QSize(width,height));

        setPixmap(scaled);
    }




    this->setPos(xCoord,yCoord);

}

void target::boom()
{
    game->explosion1(xCoord, yCoord );
    deleteLater();
    return;
}

void target::smallBoom()
{
    game->explosion2(xCoord,yCoord);
    deleteLater();
    return;
}

void target::collision()
{
    game->explosion1(game->player->x(), game->player->y());
    deleteLater();
    return;
}

void target::smallCollision()
{
    game->explosion2(game->getPlayerXPos(),game->getPlayerYPos());
    deleteLater();
    return;
}
