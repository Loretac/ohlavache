#ifndef FOE3_H
#define FOE3_H

#include "enemy.h"

/*********************************************************************
 **
 *********************************************************************/

class Foe3 : public enemy
{
    Q_OBJECT
public:
    Foe3();

private slots:
    virtual void move();
    void shoot();

private:
    void startShooting();
};

#endif // FOE3_H
