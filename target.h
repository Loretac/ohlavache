#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class target : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    target();
    double xCoord;
    double yCoord;

public slots:
    void boom();
};

#endif // TARGET_H
