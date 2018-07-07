#ifndef BULLETTARGETEDLARGE_H
#define BULLETTARGETEDLARGE_H

#include "enemybullet.h"

/*********************************************************************
 **
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
