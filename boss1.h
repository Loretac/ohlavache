#ifndef BOSS1_H
#define BOSS1_H

#include "enemy.h"

/*********************************************************************
 ** Level 1 boss
 *********************************************************************/

class Boss1 : public enemy
{
    Q_OBJECT
public:
    Boss1();

private slots:
    virtual void move();

signals:
    void bossDeath(); // received by levels::spawnBoss1() to begin Level 2

private:
    void startShooting(); // continuously shoot bullets on a timer
};

#endif // BOSS1_H
