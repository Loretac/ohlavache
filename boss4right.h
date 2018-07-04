#ifndef BOSS4RIGHT_H
#define BOSS4RIGHT_H

#include "enemy.h"
#include "laser.h"
#include "target.h"

class Boss4Right : public enemy
{
    Q_OBJECT
public:
    Boss4Right();

private slots:
    virtual void move();
    void shoot();
    void setTarget();
    void positionLaser();
    void laserOff();
    void laserOn();
    void makeCalls();

signals:
    void rightBossDeath();

private:
    bool moveUp = false;
    Laser *laser;
    double targetX;
    double targetY;
    double speed = 3;
    bool bossLeftDead = false; // left boss calls commands unless it dies
};

#endif // BOSS4RIGHT_H
