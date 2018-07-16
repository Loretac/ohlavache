#ifndef LEVELS_H
#define LEVELS_H

#include <QObject>

/*********************************************************************
 ** Levels class - manages all spawns and level advances
 *********************************************************************/

class levels : public QObject
{
    Q_OBJECT

public:
    levels();

public slots:
    void spawnFoe1();
    void spawnFoe2();
    void spawnFoe3();
    void spawnFoe4();

    void spawnBoss1();
    void spawnBoss2();
    void spawnBoss3();
    void spawnBoss4();

    void level1();
    void level2();
    void level3();
    void level4();

};

#endif // LEVELS_H
