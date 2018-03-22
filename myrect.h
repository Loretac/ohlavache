#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>

// to help handle signals and slots
#include <QObject>


class MyRect:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);
public slots:
    void spawn(); // connected to timer so that we can periodically spawn enemies
};

#endif // MYRECT_H
