#ifndef BULLETTARGETEDSMALL_H
#define BULLETTARGETEDSMALL_H

#include "enemybullet.h"

/*********************************************************************
 ** Small bomb that explodes either upon reaching its destination or
 ** colliding with player. Shot by Level 3 foe
 *********************************************************************/

class BulletTargetedSmall : public EnemyBullet
{
    Q_OBJECT
public:
    BulletTargetedSmall();

private slots:
    virtual void move();

signals:
    void arrived();
    void collide();
};

#endif // BULLETTARGETEDSMALL_H
