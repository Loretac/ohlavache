#ifndef BULLETTARGETEDSMALL_H
#define BULLETTARGETEDSMALL_H

#include "enemybullet.h"

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
