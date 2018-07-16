#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QGraphicsPixmapItem>

/*********************************************************************
 ** Target class for targeted bombs
 *********************************************************************/

class target : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    target(int size); // 1=Large, 2=Small
    double xCoord;
    double yCoord;
    int getWidth();
    int getHeight();

public slots:
    void boom();
    void smallBoom();
    void collision();
    void smallCollision();

private:
    int width;
    int height;
};

#endif // TARGET_H
