#ifndef ENEMY_H
#define ENEMY_H



#include <QGraphicsPixmapItem>
#include <QObject>

class Enemy: public QObject, public QGraphicsItemGroup{ //QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(int type, int health);
    void damage();

signals:
    void boss1Dead();

private:
    int enemyType;
    void checkCollision();

    bool moveLeft = false;          // boolean to keep track of l/r direction of enemy
    int health;                     // current amount of health
    int startingHealth;
    QGraphicsPixmapItem *enemyPix;  // image of enemy
    QGraphicsPixmapItem *healthPix; // image of healthbar
    double currXCoord;
    double currYCoord;
    std::string size;               // S, M, etc.

    int width;                      // width of enemy image
    int height;                     // height of enemy image

    int hbX;                        // x-position of health bar
    int hbY;                        // y-position of health bar

    // These should reflect # of divisions each size of health bar
    const int S_BAR_SIZE = 2;
    const int M_BAR_SIZE = 4;
    int barsize;                    // this enemy's health bar size

public slots:
    void boss1Shoot();
    void boss2Shoot();
    void shoot2();
    void move1();
    void move2();
};







#endif // ENEMY_H



