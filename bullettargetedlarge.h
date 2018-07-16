#ifndef BULLETTARGETEDLARGE_H
#define BULLETTARGETEDLARGE_H

#include "enemybullet.h"

/*********************************************************************
 ** Large bomb that explodes either upon reaching its destination or
 ** colliding with player. Shot by Level 2 boss
 *********************************************************************/

class BulletTargetedLarge : public EnemyBullet
{
    Q_OBJECT
public:
    BulletTargetedLarge();

private slots:
    virtual void move();

signals:
    void arrived();
    void collide();
};

#endif // BULLETTARGETEDLARGE_H
