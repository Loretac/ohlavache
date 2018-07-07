#include "enemybullet.h"

#include <QTimer>

/*********************************************************************
 **
 *********************************************************************/

void EnemyBullet::setBulletPix(QPixmap map)
{
    QPixmap scaled = map.scaled(getWidth(),getHeight());

    setPixmap(scaled);
}

void EnemyBullet::setDimensions(int pixwidth, int pixheight)
{
    width = pixwidth;
    height = pixheight;
}

int EnemyBullet::getCounter()
{
    return counter;
}

void EnemyBullet::setCounter(int val)
{
    counter = val;
}



int EnemyBullet::getWidth()
{
    return width;
}

int EnemyBullet::getHeight()
{
    return height;
}

void EnemyBullet::setSpeed(double val)
{
    speed = val;
}

int EnemyBullet::getSpeed()
{
    return speed;
}

void EnemyBullet::setXTrajectory(double val)
{
    xTrajectory = val;
}

void EnemyBullet::setYTrajectory(double val)
{
    yTrajectory = val;
}

double EnemyBullet::getXTrajectory()
{
    return xTrajectory;
}

double EnemyBullet::getYTrajectory()
{
    return yTrajectory;
}

void EnemyBullet::setMotion()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this,SLOT(move()));

    timer->start(5);
}

void EnemyBullet::checkStatus()
{
    if(pos().y() > 600 ||
            pos().y()+height < -100 ||
            pos().x() > 800 ||
            pos().x() + width < 0){
        deleteLater();
    }
}
