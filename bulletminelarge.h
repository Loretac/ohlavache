#ifndef BULLETMINELARGE_H
#define BULLETMINELARGE_H

#include "enemybullet.h"

/*********************************************************************
 ** Large mine (bomb that explodes on contact) shot by Level 3 boss
 *********************************************************************/

class BulletMineLarge : public EnemyBullet
{
    Q_OBJECT
public:
    BulletMineLarge();

private slots:
    virtual void move();
};

#endif // BULLETMINELARGE_H
