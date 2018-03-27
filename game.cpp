#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

// because we want to connect a timer to a function that constantly creates enemies
#include <QTimer>

#include "game.h"
#include "enemy.h"
#include "player.h"


Game::Game(QWidget *parent){


    // create a scene
    scene = new QGraphicsScene();

    // create an item to put into the scene
    // by default, length and width are 0
    player = new Player();

    // change rectangle to 100x100 pix

    // player->setRect(0,0,100,100);
    // player->setPixmap(QPixmap(":/images/jet.png"));

    // make rect focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();



    // add the item to the scene
    scene->addItem(player);

    // make the scene 800x600 instead of infinity by infinity (default)
    scene->setSceneRect(0,0,800,600);

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);


    // initialize the player at the bottom
    player->setPos(350,500); // TODO generalize to always be in the middle bottom of screen

    // create the score and health
    score = new Score();
    health = new Health();

    // add the score to the scene
    scene->addItem(score);

    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);

    // spawn enemies
    QTimer *timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000); // new enemy created every 2000 ms (2 seconds)



    show();


}
