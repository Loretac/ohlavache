#include "button.h"
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QBrush>


/*********************************************************************
 ** Button constructor.
 *********************************************************************/
Button::Button(QString name, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    // draw the rectangle
    setRect(0,0,200,50);

    // change the color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    //draw the text
    text = new QGraphicsTextItem(name,this);

    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;

    text->setPos(xPos,yPos);

    // allow responding to hover events
    setAcceptHoverEvents(true);

}

/*********************************************************************
 ** Intercept the mousePressEvent function with clicked() signal.
 *********************************************************************/
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

/*********************************************************************
 ** Intercept the hoverEnterEvent to change color if active
 *********************************************************************/
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // change color when hovered
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}

/*********************************************************************
 ** Intercept the hoverLeaveEvent to default color when active
 *********************************************************************/
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // change the color back to default
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}

