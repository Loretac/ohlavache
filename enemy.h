#ifndef ENEMY_H
#define ENEMY_H



#include <QGraphicsPixmapItem>
#include <QObject>

class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(int);
    bool moveLeft = false;

public slots:
    void move1();
    void move2();
};







#endif // ENEMY_H



