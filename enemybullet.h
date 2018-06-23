#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class enemybullet : public QObject, public QGraphicsPixmapItem{
     Q_OBJECT
public:
    enemybullet();
    void checkCollision();
    int xCoord;
    int yCoord;
public slots:
    void move();
};

#endif // ENEMYBULLET_H
