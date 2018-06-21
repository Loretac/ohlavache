#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

// for scene background
#include <QImage>

#include <QtDebug>

// because we want to connect a timer to a function that constantly creates enemies
#include <QTimer>

#include "game.h"
#include "enemy.h"
#include "player.h"
#include "lives.h"
#include "button.h"
#include "levels.h"

/*********************************************************************
 ** Game constructor. This function runs only once, as each time
 ** the application opens only one instance of Game is created.
 *********************************************************************/
Game::Game(QWidget *parent){

    // SET UP THE SCENE

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

/*********************************************************************
 ** The opening menu of the game. Called only once upon opening
 ** the application.
 *********************************************************************/
void Game::displayMainMenu()
{
    // create the title
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Shooter Game"));

    // make font bigger
    QFont titleFont("times",50);
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

/*********************************************************************
 ** The death function is called every time the player dies.
 *********************************************************************/
void Game::death()
{
    //qDebug() << "Death.";
    // delete the player
    delete(player);

    // create a new player
    player = new Player();

    // show the player
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);
    player->setPos(350,500);

    // decrease lives
    delete(lifeArray[numLives-1]);
    numLives--;

    qDebug() << "Death. Checking lives...";

    // if no more lives, game over
    if(numLives<=0){
        gameOver();
    }
}

/*********************************************************************
 ** This function starts the gameplay. It can be called at the
 ** opening of the application, or upon restart after the game is
 ** over. To be safe, it clears the screen regardless.
 *********************************************************************/
void Game::start()
{
    // clear the screen
    scene->clear();

    // re-initialize paused to false
    paused = false;

    // create the player
    player = new Player();

    // make focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add the item to the scene
    scene->addItem(player);

    // initialize the player at the bottom
    player->setPos(350,500); // TODO generalize to always be in the middle bottom of screen

    // create the score
    score = new Score();

    // add the score to the scene
    scene->addItem(score);

    numLives = 3; // initialize lives to 3

    // display the lives to the screen
    for(int i = 0; i < numLives; i++){
        lifeArray[i] = new Lives;
        // bottom left corner, from left to right
        lifeArray[i]->setPos(lifeArray[i]->x()+40*i + 10,lifeArray[i]->y()+550);
        scene->addItem(lifeArray[i]);
    }


    show();

    // spawn enemies
    //QTimer::singleShot(400, this, SLOT(spawn()));
    //QTimer::singleShot(800, this, SLOT(spawn()));

    //levels *mylevels = new levels();

    myLevels = new levels();

    //mylevels->level1();


    // spawn enemies
    //timer = new QTimer();
    //QObject::connect(timer,SIGNAL(timeout()),this,SLOT(spawn()));
    //timer->start(400); // new enemy created every x ms



}

/*********************************************************************
 ** Prepares for a new game... delete old objects
 *********************************************************************/
void Game::restartGame()
{
    delete(player);
    delete(score);
    delete(myLevels);

    // no need to delete lives... at this point there are none

    start();
}

/*********************************************************************
 ** Spawns enemies based on timer in game.cpp
 *********************************************************************/
//void Game::spawn()
//{
//        // create an enemy
//        Enemy *enemy = new Enemy();

//        // add to the scene
//        scene->addItem(enemy);
//}

/*********************************************************************
 ** Runs when player has run out of lives.
 *********************************************************************/
void Game::gameOver()
{

    // pause all movement on the screen
    paused = true;

    // disable all scene items
    for(size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(false);
    }

    QString message= "Game Over!";
    displayGameOverWindow(message);

}

/*********************************************************************
 ** This function displays the game over window after the game
 ** is complete. A new game is started if the button is clicked.
 *********************************************************************/
void Game::displayGameOverWindow(QString textToDisplay)
{
    drawPanel(0,0,800,600,Qt::black,0.65);

    // create play again button
    Button *playAgain = new Button(QString("Play Again"));
    playAgain->setPos(410,500);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));
}

/*********************************************************************
 ** This function creates an overlay while menus are displaying.
 *********************************************************************/
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

