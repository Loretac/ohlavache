#ifndef BULLETSIMPLE_H
#define BULLETSIMPLE_H

#include "enemybullet.h"

/*********************************************************************
 ** Bullet that moves in straight downward direction, shot by Level 1
 ** boss.
 *********************************************************************/

class BulletSimple : public EnemyBullet
{
    Q_OBJECT
public:
    BulletSimple();

private slots:
    virtual void move();
};

#endif // BULLETSIMPLE_H
