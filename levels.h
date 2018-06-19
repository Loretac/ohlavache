#ifndef LEVELS_H
#define LEVELS_H

#include <QObject>

class levels : public QObject
{
    Q_OBJECT

public:
    levels();
    void level1();
    void level2();

public slots:
    void spawn1();
    void spawn2();
};

#endif // LEVELS_H
