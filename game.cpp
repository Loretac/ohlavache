#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

// for scene background
#include <QImage>

#include <QtDebug>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include <math.h> // sin, cos

#include <stdlib.h> // rand

#include <iostream>
#include <vector>

// because we want to connect a timer to a function that constantly creates enemies
#include <QTimer>

#include "game.h"
//#include "enemytemp.h"
#include "player.h"
#include "button.h"
#include "levels.h"
#include "target.h"

#include "bulletdirected.h"


//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */




//#include "enemybullettemp.h"

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
    setBackgroundBrush(QBrush(QImage(":/images/images/paris.png")));

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
    emit dying();
    invincibility = true; // player cannot take/deal collision damage

    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    //player->setGraphicsEffect();
    player->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(1350);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    connect(a,SIGNAL(finished()),this,SLOT(resetPlayer()));



}

bool Game::isPaused()
{
    return paused;
}

/*********************************************************************
 ** This function starts the gameplay. It can be called at the
 ** opening of the application, or upon restart after the game is
 ** over. To be safe, it clears the screen regardless.
 *********************************************************************/
void Game::start()
{
    //srand (time(NULL));

    // clear the screen
    scene->clear();

    // re-initialize paused to false
    paused = false;

    // create the player
    player = new Player();

    invincibility = false;

    laserTarget = new target(3);

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
    //scene->addItem(score);

    numLives = 3; // initialize lives to 3

    for(int i = 0; i < numLives-1; i++){
        QGraphicsPixmapItem *life = new QGraphicsPixmapItem();
        life->setPixmap(QPixmap(":/images/images/life.png"));
        lives.push_back(life);

        lives[i]->setPos(lives[i]->x()+40*i + 10, lives[i]->y()+550);
        scene->addItem(lives[i]);
    }


    show();

    myLevels = new levels();



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

void Game::targetFollow()
{
    if(!paused){
        QTimer::singleShot(0, this, SLOT(laserTargetOn()));
        QTimer::singleShot(250, this, SLOT(laserTargetOff()));
        QTimer::singleShot(1250, this, SLOT(laserTargetOn()));
        QTimer::singleShot(1500, this, SLOT(laserTargetOff()));
        QTimer::singleShot(2500, this, SLOT(finalTarget()));
        QTimer::singleShot(3500, this, SLOT(readyToFire()));
    }



}

void Game::finalTarget()
{
    if(!paused){
        targetedXCoord = player->x() + player->getwidth()/2 - laserTarget->getWidth()/2;
        targetedYCoord = player->y() + player->getheight()/2 - laserTarget->getHeight()/2;

        laserTargetOn();
    }

}

void Game::readyToFire()
{
    if(!paused){
        emit fire();
        laserTargetOff();

        QTimer::singleShot(500, this, SLOT(readyToStop()));
    }


}

// sends a signal linked to boss4 slots to stop firing lasers
void Game::readyToStop()
{
    emit stopFiring();
}

void Game::invincibilityOff()
{
    invincibility = false;
    player->showImage();
}

void Game::resetPlayer()
{
    delete(player);

    // create a new player
    player = new Player();

    // show the player
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);
    player->setPos(350,500);

    numLives--;


    if(numLives > 0){
        // remove life from screen
        scene->removeItem(lives.back());

        // erase from vector
        lives.erase(lives.end()-1);
    }

    //qDebug() << "Death. Checking lives...";

    // if no more lives, game over
    if(numLives<=0){
        gameOver();
        return;
    }


        QTimer::singleShot(100, player, SLOT(hideImage()));
        QTimer::singleShot(200, player, SLOT(showImage()));
        QTimer::singleShot(300, player, SLOT(hideImage()));
        QTimer::singleShot(400, player, SLOT(showImage()));
        QTimer::singleShot(500, player, SLOT(hideImage()));
        QTimer::singleShot(600, player, SLOT(showImage()));
        QTimer::singleShot(700, player, SLOT(hideImage()));
        QTimer::singleShot(800, player, SLOT(showImage()));
        QTimer::singleShot(900, player, SLOT(hideImage()));
        QTimer::singleShot(1000, player, SLOT(showImage()));
        QTimer::singleShot(1100, player, SLOT(hideImage()));
        QTimer::singleShot(1200, player, SLOT(showImage()));
        QTimer::singleShot(1300, player, SLOT(hideImage()));
        QTimer::singleShot(1400, player, SLOT(showImage()));
        QTimer::singleShot(1500, player, SLOT(hideImage()));
        QTimer::singleShot(1600, this, SLOT(invincibilityOff()));




}

void Game::playerShow()
{
    scene->removeItem(player);
}

void Game::playerHide()
{
    scene->addItem(player);
}

void Game::laserTargetOn()
{
    laserTarget->setPos(player->x() + player->getwidth()/2 - laserTarget->getWidth()/2, player->y() + player->getheight()/2 - laserTarget->getHeight()/2);

    //myTarget->setPos(player->x() + game->getPlayerWidth()/2 - playerTarget->getWidth()/2, game->getPlayerYPos() + game->getPlayerHeight()/2 - playerTarget->getHeight()/2);
    scene->addItem(laserTarget);
    //qDebug() << "laser target turned on";
}

void Game::laserTargetOff()
{
    scene->removeItem(laserTarget);
}


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

void Game::explosion1(double xPos, double yPos)
{

    double angle = rand()%360;

    for(int i = 0; i < 7; i++){
        BulletDirected *Bullet = new BulletDirected;
        Bullet->setSpeed(10);
        Bullet->setPos(xPos+25,yPos+25);

        Bullet->setXTrajectory(cos(angle*M_PI/180));
        Bullet->setYTrajectory(sin(angle*M_PI/180));

        angle += 51.43;

        addToScene(Bullet);
    }


}

void Game::explosion2(double xPos, double yPos)
{
    double angle = rand()%360;

    for(int i = 0; i < 3; i++){
        BulletDirected *Bullet = new BulletDirected();
        Bullet->setSpeed(10);
        Bullet->setPos(xPos+25,yPos+25);

        Bullet->setXTrajectory(cos(angle*M_PI/180));
        Bullet->setYTrajectory(sin(angle*M_PI/180));

        angle += 120;

        scene->addItem(Bullet);
    }
}

void Game::explosion3(double xPos, double yPos)
{

    double angle = rand()%360;

    for(int i = 0; i < 15; i++){
        BulletDirected *Bullet = new BulletDirected;
        Bullet->setSpeed(10);
        Bullet->setPos(xPos+25,yPos+25);

        Bullet->setXTrajectory(cos(angle*M_PI/180));
        Bullet->setYTrajectory(sin(angle*M_PI/180));

        angle += 24;

        addToScene(Bullet);
    }

}

int Game::getPlayerXPos()
{
    return player->x();
}

int Game::getPlayerYPos()
{
    return player->y();
}

int Game::getPlayerWidth()
{
    return player->getwidth();
}

int Game::getPlayerHeight()
{
    return player->getheight();
}

double Game::getTargetedX()
{
    return targetedXCoord;
}

double Game::getTargetedY()
{
    return targetedYCoord;
}

void Game::removeFromScene(QGraphicsItem *item)
{
    scene->removeItem(item);
}

void Game::addToScene(QGraphicsItem *item)
{
    scene->addItem(item);
}

bool Game::isInvincible()
{
    return invincibility;
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


