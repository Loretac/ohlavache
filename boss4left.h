#ifndef BOSS4LEFT_H
#define BOSS4LEFT_H

#include "enemy.h"
#include "laser.h"
#include "target.h"

class Boss4Left : public enemy
{
    Q_OBJECT
public:
    Boss4Left();

private slots:
    virtual void move();
    void shoot();
    void positionLaser();
    void laserOff();
    void laserOn();

signals:
    void bossDeath();

private:
    bool moveUp = false;
    Laser *laser;
    double targetX;
    double targetY;
};

#endif // BOSS4LEFT_H
