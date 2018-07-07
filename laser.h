#ifndef LASER_H
#define LASER_H

#include <QObject>
#include <QGraphicsPixmapItem>

/*********************************************************************
 **
 *********************************************************************/

class Laser : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Laser();
//    void setSourceX(double);
//    void setSourceY(double);
//    void setTargetX(double);
//    void setTargetY(double);

public slots:
    void move();

private:
    double angle;
    double sourceX;
    double sourceY;
    double targetX;
    double targetY;

};

#endif // LASER_H
