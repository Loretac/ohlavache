#ifndef BULLETSIMPLE_H
#define BULLETSIMPLE_H

#include "enemybullet.h"

class BulletSimple : public EnemyBullet
{
    Q_OBJECT
public:
    BulletSimple();

private slots:
    virtual void move();
};

#endif // BULLETSIMPLE_H
