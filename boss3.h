#ifndef BOSS3_H
#define BOSS3_H

#include "enemy.h"

/*********************************************************************
 ** Level 3 boss
 *********************************************************************/

class Boss3 : public enemy
{
    Q_OBJECT
public:
    Boss3();

private slots:
    virtual void move();
    void shoot(); // fires a single bomb
    void rapidFire(); // shoots a stream of explode-on-contact bombs

signals:
    void bossDeath(); // received by levels::spawnBoss2() to begin Level 3

private:
    int fireCounter = 0; // incrementer for rapidFire()
};

#endif // BOSS3_H
