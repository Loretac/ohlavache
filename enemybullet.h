#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include "game.h"

/*********************************************************************
 **
 *********************************************************************/

class EnemyBullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    void setBulletPix(QPixmap);

    void setDimensions(int width, int height);

    int getCounter();
    void setCounter(int);

    int getWidth();
    int getHeight();

    void setSpeed(double);
    int getSpeed();

    void setXTrajectory(double);
    void setYTrajectory(double);

    double getXTrajectory();
    double getYTrajectory();

    void setMotion();

    void checkStatus();

private:
    int counter = 0;

    double speed = 10;

    int width;
    int height;

    double xTrajectory;
    double yTrajectory;

private slots:
    virtual void move() = 0;
};

#endif // ENEMYBULLET_H
