#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

/*********************************************************************
 ** Virtual class for enemy bullet types.
 *********************************************************************/

class EnemyBullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    void setBulletPix(QPixmap); // set the image

    // getter/setter for counter
    int getCounter();
    void setCounter(int);

    // getter/setter for dimensions
    int getWidth();
    int getHeight();
    void setDimensions(int width, int height);

    // getter/setter for speed
    void setSpeed(double);
    int getSpeed();

    // getter/setter for trajectory
    void setXTrajectory(double);
    void setYTrajectory(double);
    double getXTrajectory();
    double getYTrajectory();

    void setMotion();

    void checkStatus();

private:
    int counter = 0; // pythagorean counter for directed targeted bullets

    double speed = 10;

    int width;
    int height;

    double xTrajectory;
    double yTrajectory;

private slots:
    virtual void move() = 0;
};

#endif // ENEMYBULLET_H
