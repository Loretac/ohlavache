#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include "game.h"

/*********************************************************************
 **
 *********************************************************************/

class enemy : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    void setEnemyPix(QPixmap);
    void setHealthPix(QPixmap);

    QGraphicsPixmapItem* getEnemyPix();
    QGraphicsPixmapItem* getHealthPix();

    void setDimensions(int width, int height, int hbX, int hbY);

    void setHealth(int);
    void setStartingHealth(int);
    int getHealth();
    int getStartingHealth();

    void positionHealth();

    int getWidth();
    int getHeight();
    int getHBX();
    int getHBY();

    bool isDead();
    void setMotion();

    void setSize(std::string);

    bool getMoveLeft();
    void setMoveLeft(bool);

signals:
    //virtual void enemyDeath() = 0;

private:

    std::string size; // S, M, L, X
    int startingHealth;
    int health;

    double currXCoord;
    double currYCoord;

    bool moveLeft = false;

    bool dead = false;

    int width;
    int height;

    int hbX;
    int hbY;

    QGraphicsPixmapItem *enemyPix;  // image of enemy
    QGraphicsPixmapItem *healthPix; // image of healthbar

    // These should reflect # of divisions each size of health bar
    const int S_BAR_SIZE = 2;
    const int M_BAR_SIZE = 4;
    int barsize;                    // this enemy's health bar size

protected: // only derived classes can access
    void checkStatus();
    void damage(); // may need relocation to public

private slots:
    virtual void move() = 0; // must be overwritten by derived classes!
};

#endif // ENEMY_H
