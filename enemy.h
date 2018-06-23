#ifndef ENEMY_H
#define ENEMY_H



#include <QGraphicsPixmapItem>
#include <QObject>

class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(int, int);
    void checkCollision();
    void damage();
    bool moveLeft = false;
    int health;

signals:
    void bossDead();

public slots:
    void shoot();
    void move1();
    void move2();
};







#endif // ENEMY_H



