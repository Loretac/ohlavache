#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsPixmapItem>

// to help handle signals and slots
#include <QObject>

/*********************************************************************
 **
 *********************************************************************/

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    bool keyLeft = false, keyRight = false, keyUp = false, keyDown = false, keySpace = false; // test

    Player(QGraphicsItem *parent=0);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    int getwidth();
    int getheight();

public slots:
    void movePlayer();
    void shoot();
    void paralyzed(); // animation when player dies
    void hideImage();
    void showImage();

private:
    int width;
    int height;
    QTimer *movementTimer;
    QTimer *shootingTimer;
    QPixmap playerPix = QPixmap(":/images/images/rocket.png");



};

#endif // MYRECT_H
