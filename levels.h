#ifndef LEVELS_H
#define LEVELS_H

#include <QObject>

class levels : public QObject
{
    Q_OBJECT

public:
    levels();
    void level1();


public slots:
    void spawn1();
    void spawnBoss1();
    void spawn2();
    void spawnBoss2();
    void spawnBoss3();
    void spawn3();
    void level2();
    void level3();
};

#endif // LEVELS_H
