#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

/*********************************************************************
 **
 *********************************************************************/

class PlayerBullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    PlayerBullet();
    int getwidth();
    int getheight();

public slots:
    void move();

private:
    int height;
    int width;

};

#endif // BULLET_H
