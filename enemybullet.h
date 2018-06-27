#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class enemybullet : public QObject, public QGraphicsPixmapItem{
     Q_OBJECT
public:
    enemybullet(int); // constructor
    //enemybullet(double,double); // constructor for bullets from bomb
    void checkCollision();

    // coordinates for trajectory of bullet
    double xCoord;
    double yCoord;

    int type;

    // getters for trajectory coordinates
    void getX(double); // should be renamed to setX and setY
    void getY(double);

    int counter = 0;

    double speed = 10;
    void setSpeed(double);

signals:
    void arrived();
    void collide();

public slots:
    void move();
    void move2();
    void move3();
    //void move4();
};

#endif // ENEMYBULLET_H
