#ifndef LEVELS_H
#define LEVELS_H

#include <QObject>
//#include <vector>

#include<forward_list> // more efficient than vector for erasing

/*********************************************************************
 **
 *********************************************************************/

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
