#ifndef BULLETMINELARGE_H
#define BULLETMINELARGE_H

#include "enemybullet.h"

class BulletMineLarge : public EnemyBullet
{
    Q_OBJECT
public:
    BulletMineLarge();

private slots:
    virtual void move();
};

#endif // BULLETMINELARGE_H
