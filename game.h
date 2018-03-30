#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "player.h"
#include "score.h"
#include "health.h"
#include "lives.h"


class Game: public QGraphicsView{
    Q_OBJECT
  public:
    Game(QWidget *parent = 0);

    // public methods
    void displayMainMenu();




    QGraphicsScene *scene;
    Player *player;
    Score *score;
    Health *health;
    Lives *lives;

    QTimer *timer;

    bool paused = false;

    void gameOver();
    void displayGameOverWindow(QString textToDisplay);


public slots:
    void start();
    void restartGame();


private:
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);

};

#endif // GAME_H
