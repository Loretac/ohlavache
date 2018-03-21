#include <QApplication>
#include <QGraphicsScene>
#include "myrect.h"
#include <QGraphicsView>




/*
 * QGraphicsScene
 * QGraphicsItem (QGraphicsRectItem - inherits from QGraphicsItem abstract class)
 * QGraphicsView
 *
 *
 * Created based on tutorial from Abdullah Aghazadah
 * Youtube channel:
 * https://www.youtube.com/channel/UClzV7jGJREjvCTzfGTrdrkQ
 *
 * */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create a scene
    QGraphicsScene *scene = new QGraphicsScene();

    // create an item to put into the scene
    // by default, length and width are 0
    MyRect *player = new MyRect();

    // change rectangle
    player->setRect(0,0,100,100);

    // add the item to the scene
    scene->addItem(player);

    // make rect focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // visualize the scene... add a view
    QGraphicsView *view = new QGraphicsView(scene);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // make view visible
    view->show();
    view->setFixedSize(800,600);
    scene->setSceneRect(0,0,800,600);

    // initialize player at the bottom
    player->setPos(view->width()/2 - player->rect().width()/2,view->height()-player->rect().height());


    return a.exec();
}
