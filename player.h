#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsPixmapItem>

// to help handle signals and slots
#include <QObject>


class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    // Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
public:
    Player(QGraphicsItem *parent=0);
    void keyPressEvent(QKeyEvent *event);
public slots:
    void spawn(); // connected to timer so that we can periodically spawn enemies
};

#endif // MYRECT_H
