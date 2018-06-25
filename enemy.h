#ifndef ENEMY_H
#define ENEMY_H



#include <QGraphicsPixmapItem>
#include <QObject>

class Enemy: public QObject, public QGraphicsItemGroup{ //QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(int, int);
    int enemyType;
    void checkCollision();
    void damage();
    bool moveLeft = false;
    int health;
    int startingHealth;
    QGraphicsPixmapItem *enemyPix; // image of enemy
    QGraphicsPixmapItem *healthPix; // image of healthbar
    int randomstart;
    double currXCoord;
    double currYCoord;

signals:
    void bossDead();

public slots:
    void shoot();
    void move1();
    void move2();
};







#endif // ENEMY_H



