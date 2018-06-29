#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class target : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    target(int size); // 1=Large, 2=Small
    double xCoord;
    double yCoord;

public slots:
    void boom();
    void smallBoom();
    void deleteTarget();

private:
    int width;
    int height;
};

#endif // TARGET_H
