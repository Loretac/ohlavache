#ifndef BOSS3_H
#define BOSS3_H

#include "enemy.h"

class Boss3 : public enemy
{
    Q_OBJECT
public:
    Boss3();

private slots:
    virtual void move();
    void shoot();
    void normalFire();
    void rapidFire();

signals:
    void bossDeath();

private:
    void startShooting();
    int fireCounter = 0;
};

#endif // BOSS3_H
