#ifndef BOSS1_H
#define BOSS1_H

#include "enemy.h"

class Boss1 : public enemy
{
    Q_OBJECT
public:
    Boss1();

private slots:
    virtual void move();
    void shoot();

signals:
    void bossDeath();

private:
    void startShooting();
};

#endif // BOSS1_H
