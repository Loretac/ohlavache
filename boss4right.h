#ifndef BOSS4RIGHT_H
#define BOSS4RIGHT_H

#include "enemy.h"
#include "laser.h"

/*********************************************************************
 ** Level 4 boss (right side)
 *********************************************************************/

class Boss4Right : public enemy
{
    Q_OBJECT
public:
    Boss4Right();

private slots:
    virtual void move();
    void shoot();

    void positionLaser();
    void laserOff();
    void laserOn();

signals:
    void rightBossDeath();

private:
    bool moveUp = false;
    Laser *laser;
    double targetX;
    double targetY;
    double speed = 3;
    bool spawning = true;
};

#endif // BOSS4RIGHT_H
