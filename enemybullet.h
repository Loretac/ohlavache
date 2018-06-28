#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class enemybullet : public QObject, public QGraphicsPixmapItem{
     Q_OBJECT
public:
    enemybullet(int); // constructor


    // setters for trajectory coordinates
    void setXtrajectory(double);
    void setYtrajectory(double);

    void setSpeed(double);

    int getwidth();
    int getheight();

signals:
    void arrived();
    void collide();

private:
    // coordinates for trajectory of bullet
    double xTrajectory;
    double yTrajectory;

    int type;
    int counter = 0;

    double speed = 10;
    void checkCollision();

    int width;
    int height;

public slots:
    void move();
    void move2();
    void move3();
};

#endif // ENEMYBULLET_H
