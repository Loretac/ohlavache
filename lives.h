#ifndef LIVES_H
#define LIVES_H

#include <QGraphicsPixmapItem>


#include <QObject>

class Lives : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Lives(QGraphicsItem *parent = 0);

};

#endif // LIVES_H
