#ifndef BUTTON_H
#define BUTTON_H


#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include <QIcon>


class Button:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    // constructor
    Button(QString name, QGraphicsItem *parent = 0);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    int width = 200;
    int height = 75;


signals:
    void clicked();


private:
    QGraphicsTextItem *text;
    QPixmap buttonPix;
    QPixmap hoverPix;
};

#endif // BUTTON_H
