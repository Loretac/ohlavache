#ifndef FOE4_H
#define FOE4_H

#include "enemy.h"

/*********************************************************************
 ** Standard enemy for Level 4; shoots small mines
 *********************************************************************/

class Foe4 : public enemy
{
    Q_OBJECT
public:
    Foe4();

private slots:
    virtual void move();
    void shoot();

private:
    void startShooting();
};

#endif // FOE4_H
