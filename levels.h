#ifndef LEVELS_H
#define LEVELS_H

#include <QObject>
//#include <vector>

#include<forward_list> // more efficient than vector for erasing

class levels : public QObject
{
    Q_OBJECT

public:
    levels();
    //void level1();


public slots:
    void spawnFoe1();
    void spawnFoe2();
    void spawnFoe3();

    void spawnBoss1();
    void spawnBoss2();



    void level1();
    void level2();
    void level3();

//    void spawn1();

//    void spawn2();
//    void spawnBoss2();
//    void spawnBoss3();
//    void spawn3();

//    void level3();

private:
    //std::vector <QObject*> activeItems;
    //std::forward_list<QObject*> activeItems;

private slots:
    //void clearInactive();
};

#endif // LEVELS_H
