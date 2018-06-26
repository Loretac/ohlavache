#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class enemybullet : public QObject, public QGraphicsPixmapItem{
     Q_OBJECT
public:
    enemybullet(int);
    void checkCollision();
    double xCoord;
    double yCoord;
    int type;

    void getX(int);
    void getY(int);

public slots:
    void move();
    void move2();
};

#endif // ENEMYBULLET_H
