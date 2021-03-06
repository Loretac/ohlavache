#ifndef FOE2_H
#define FOE2_H

#include "enemy.h"

/*********************************************************************
 ** Standard enemy for Level 2; shoots directed bullets
 *********************************************************************/

class Foe2 : public enemy
{
    Q_OBJECT
public:
    Foe2();

private slots:
    virtual void move();
    void shoot();

private:
    void startShooting();
};

#endif // FOE2_H
