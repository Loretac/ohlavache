#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsPixmapItem>

// to help handle signals and slots
#include <QObject>


class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    // Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
public:
    bool keyLeft = false, keyRight = false, keyUp = false, keyDown = false, keySpace = false; // test



    Player(QGraphicsItem *parent=0);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event); // test
    //void timerEvent(QTimerEvent *event); // test

public slots:
    void movePlayer(); // test
    void spawn(); // connected to timer so that we can periodically spawn enemies
};

#endif // MYRECT_H
