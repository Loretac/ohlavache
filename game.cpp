#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

// for scene background
#include <QImage>

// because we want to connect a timer to a function that constantly creates enemies
#include <QTimer>

#include "game.h"
#include "enemy.h"
#include "player.h"
#include "lives.h"
#include "button.h"


Game::Game(QWidget *parent){

    // create a scene
    scene = new QGraphicsScene();
    // make the scene 800x600 instead of infinity by infinity (default)
    scene->setSceneRect(0,0,800,600);

    // make the background an image
    setBackgroundBrush(QBrush(QImage(":/images/skybackground.png")));


    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    displayMainMenu();



}

void Game::displayMainMenu()
{
    // create the title
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Shooter Game"));

    // make font bigger
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);

    // set position... center on x-axis
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;

    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button *playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - titleText->boundingRect().width()/2;
    int byPos = 400;
    playButton->setPos(bxPos,byPos);

    scene->addItem(playButton);

    // when play button clicked, want to start
    connect(playButton, SIGNAL(clicked()),this,SLOT(start()));
}

void Game::death()
{
    health->decrease();
    delete(player);


    player = new Player();

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);

    player->setPos(350,500);
}

void Game::start()
{
    // clear the screen
    scene->clear();

    paused = false;

    // create an item to put into the scene
    // by default, length and width are 0
    player = new Player();

    // make rect focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add the item to the scene
    scene->addItem(player);






    // initialize the player at the bottom
    player->setPos(350,500); // TODO generalize to always be in the middle bottom of screen

    // create the score and health
    score = new Score();
    health = new Health();

    // add the score to the scene
    scene->addItem(score);

    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);



    //add lives
    lives = new Lives();
    lives->setPos(lives->x()+10,lives->y()+550);
    scene->addItem(lives);

    // spawn enemies
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(spawn()));
    timer->start(2000); // new enemy created every 2000 ms (2 seconds)



    /*
    //player movement
    QTimer *movementTimer = new QTimer();
    QObject::connect(movementTimer,SIGNAL(timeout()),player,SLOT(movePlayer()));
    movementTimer->start(2);
    */

    // connect dead signal to game end
    //connect( health, SIGNAL(dead()), this, SLOT(end()) );



    show();
}

void Game::restartGame()
{
    delete(player);
    delete(score);
    delete(health);
    delete(lives);
    start();
}

/*********************************************************************
 ** Spawns enemies based on timer in game.cpp
 *********************************************************************/
void Game::spawn()
{
        // create an enemy
        Enemy *enemy = new Enemy();

        // add to the scene
        scene->addItem(enemy);


}

void Game::gameOver()
{
    paused = true;

    // stop spawning enemies
    timer->stop();

    // disable all scene items
    for(size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(false);
    }



    // pop up semi transparent panel

    QString message;

    message = "Game Over!";

    displayGameOverWindow(message);




    // QApplication::quit();
}

void Game::displayGameOverWindow(QString textToDisplay)
{
    drawPanel(0,0,800,600,Qt::black,0.65);

    // create play again button
    Button *playAgain = new Button(QString("Play Again"));
    playAgain->setPos(410,500);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));


}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    QGraphicsRectItem *panel = new QGraphicsRectItem(x,y,width,height);

    QBrush brush;
    brush.setStyle((Qt::SolidPattern));
    brush.setColor(color);

    panel->setBrush(brush);
    panel->setOpacity(opacity);

    scene->addItem(panel);
}

