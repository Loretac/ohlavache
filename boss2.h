#ifndef BOSS2_H
#define BOSS2_H

#include "enemy.h"

class Boss2 : public enemy
{
    Q_OBJECT
public:
    Boss2();

private slots:
    virtual void move();
    void shoot();

signals:
    void bossDeath();

private:
    void startShooting();
};

#endif // BOSS2_H
