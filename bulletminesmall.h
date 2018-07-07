#ifndef BULLETMINESMALL_H
#define BULLETMINESMALL_H

#include "enemybullet.h"

/*********************************************************************
 **
 *********************************************************************/

class BulletMineSmall : public EnemyBullet
{
    Q_OBJECT
public:
    BulletMineSmall();

private slots:
    virtual void move();
};

#endif // BULLETMINESMALL_H
