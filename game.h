#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "player.h"
#include "score.h"
#include "lives.h"



class Game: public QGraphicsView{
    Q_OBJECT
  public:
    Game(QWidget *parent = 0);

    // public methods
    void displayMainMenu();
    void death();

    QGraphicsScene *scene;
    Player *player;
    Score *score;

    Lives *lifeArray[3];
    int numLives = 3; // begin game with 3 lives

    QTimer *timer;

    bool paused = false;

    void gameOver();
    void displayGameOverWindow(QString textToDisplay);


public slots:
    void start();
    void restartGame();
    //void spawn(); // connected to timer so that we can periodically spawn enemies


private:
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);

};

#endif // GAME_H
