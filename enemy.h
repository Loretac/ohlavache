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
    std::string size; // S, M, etc.

    int barsize;

    // These should reflect # of divisions each size of health bar
    const int S_BAR_SIZE = 2;
    const int M_BAR_SIZE = 4;


signals:
    void boss1Dead();

public slots:
    void boss1Shoot();
    void boss2Shoot();
    void shoot2();
    void move1();
    void move2();
};







#endif // ENEMY_H



