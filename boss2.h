#ifndef BOSS2_H
#define BOSS2_H

#include "enemy.h"

/*********************************************************************
 ** Level 2 boss
 *********************************************************************/

class Boss2 : public enemy
{
    Q_OBJECT
public:
    Boss2();

private slots:
    virtual void move();
    void shoot(); // fires a single bomb

signals:
    void bossDeath(); // received by levels::spawnBoss2() to begin Level 3

private:
    void startShooting(); // member function to continuously shoot() on a timer
};

#endif // BOSS2_H
