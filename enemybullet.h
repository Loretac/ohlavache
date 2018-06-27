#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class enemybullet : public QObject, public QGraphicsPixmapItem{
     Q_OBJECT
public:
    enemybullet(int); // constructor
    void checkCollision();

    // coordinates for trajectory of bullet
    double xCoord;
    double yCoord;

    int type;

    // getters for trajectory coordinates
    void getX(int);
    void getY(int);

    int counter = 0;

signals:
    void arrived();

public slots:
    void move();
    void move2();
    void move3();
};

#endif // ENEMYBULLET_H
