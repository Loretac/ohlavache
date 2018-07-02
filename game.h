#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "player.h"
#include "score.h"
#include "levels.h"

#include <iostream>
#include <vector>


class Game: public QGraphicsView{
    Q_OBJECT
  public:
    Game(QWidget *parent = 0);

    // public methods
    void displayMainMenu();
    void death();



    Score *score;

    levels *myLevels;

    std::vector<QGraphicsPixmapItem *> lives;
    int numLives = 3; // begin game with 3 lives

    bool isPaused();

    void gameOver();
    void displayGameOverWindow(QString textToDisplay);

    void explosion1(double, double);
    void explosion2(double,double);
    void explosion3(double,double);

    int getPlayerXPos();
    int getPlayerYPos();

    int getPlayerWidth();
    int getPlayerHeight();

    void removeFromScene(QGraphicsItem* item);

    void addToScene(QGraphicsItem* item);



public slots:
    void start();
    void restartGame();


private:
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    bool paused = false;
    QGraphicsScene *scene;
    Player *player;

private slots:
};

#endif // GAME_H
