#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>

/*********************************************************************
 ** Virtual class for enemies
 *********************************************************************/

class enemy : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:

    // getter/setter for enemy and healthbar pixmaps
    void setEnemyPix(QPixmap);
    void setHealthPix(QPixmap);
    QGraphicsPixmapItem* getEnemyPix();
    QGraphicsPixmapItem* getHealthPix();

    // getter/setter for dimensions of enemy and healthbar placement
    void setDimensions(int width, int height, int hbX, int hbY);
    int getWidth();
    int getHeight();
    int getHBX();
    int getHBY();

    // getter/setter for health
    void setHealth(int);
    int getHealth();

    // getter/setter for starting health
    void setStartingHealth(int);
    int getStartingHealth();

    // positions healthbar based on hbX and hbY
    void positionHealth();

    // getter for dead
    bool isDead();

    // setter for size
    void setSize(std::string);

    // setter/getter for moveLeft (whether enemy is currentlty moving left)
    bool getMoveLeft();
    void setMoveLeft(bool);

    void setMotion();

signals:


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
