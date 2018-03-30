#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsPixmapItem>

// to help handle signals and slots
#include <QObject>


class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    bool keyLeft = false, keyRight = false, keyUp = false, keyDown = false, keySpace = false; // test



    Player(QGraphicsItem *parent=0);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    int getNumLives() const;
    void setNumLives(int value);

public slots:
    void movePlayer();
    void spawn(); // connected to timer so that we can periodically spawn enemies

private:
    int numLives;
};

#endif // MYRECT_H
