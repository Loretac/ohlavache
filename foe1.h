#ifndef FOE1_H
#define FOE1_H

#include "enemy.h"

/*********************************************************************
 ** Standard enemy for Level 1; does not shoot
 *********************************************************************/

class Foe1 : public enemy
{
    Q_OBJECT
public:
    Foe1();

private slots:
    virtual void move();

signals:
    //void enemyDeath();
};

#endif // FOE1_H
