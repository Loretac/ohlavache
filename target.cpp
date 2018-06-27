#include "target.h"
#include "game.h"

extern Game * game;

target::target()
{

    xCoord = game->player->x()+5;
    yCoord = game->player->y()+20;

    setPixmap(QPixmap(":/images/images/target.png"));


    this->setPos(xCoord,yCoord);

}

void target::boom()
{
    game->explosion1(xCoord, yCoord );
    delete this;
    return;
}

void target::deleteTarget()
{
    game->explosion1(game->player->x(), game->player->y());
    delete this;
    return;
}
