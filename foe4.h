#ifndef FOE4_H
#define FOE4_H

#include "enemy.h"

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
