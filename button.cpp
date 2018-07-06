#include "button.h"
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QBrush>

#include <QDebug>


/*********************************************************************
 ** Button constructor.
 *********************************************************************/
Button::Button(QString name, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    if(name == "Play"){
        //buttonPix = new QPixmap;
        buttonPix = QPixmap(":/images/images/playbutton.png");
        hoverPix = QPixmap(":/images/images/playbuttonhover.png");
        //QPixmap pixmap(":/images/images/playbutton.png");
        setPixmap(buttonPix);

        //QIcon ButtonIcon(pixmap);

    }
    if(name == "Play Again"){
        buttonPix = QPixmap(":/images/images/replaybutton.png");
        hoverPix = QPixmap(":/images/images/replaybuttonhover.png");

        setPixmap(buttonPix);
    }

    // draw the rectangle
    //setRect(0,0,2000,75);
    //setRect();

    // change the color
//    QBrush brush;
//    brush.setStyle(Qt::SolidPattern);
//    brush.setColor(Qt::darkCyan);
//    setBrush(brush);

    //draw the text
    //text = new QGraphicsTextItem(name,this);

    //int xPos = rect().width()/2 - text->boundingRect().width()/2;
    //int yPos = rect().height()/2 - text->boundingRect().height()/2;

    //text->setPos(xPos,yPos);

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
    setPixmap(hoverPix);
}

/*********************************************************************
 ** Intercept the hoverLeaveEvent to default color when active
 *********************************************************************/
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setPixmap(buttonPix);
}

