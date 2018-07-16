#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "player.h"
#include "score.h"
#include "levels.h"
#include "target.h"

#include <vector>

/*********************************************************************
 ** Header for main game class
 *********************************************************************/

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
    int numLives;

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

    double getTargetedX();
    double getTargetedY();

    void removeFromScene(QGraphicsItem* item);

    void addToScene(QGraphicsItem* item);
    bool isInvincible();



public slots:
    void start();
    void restartGame();
    void laserTargetOn();
    void laserTargetOff();
    void targetFollow();
    void invincibilityOff();
    void invincibilityOn();

    // while player is respawning, blinks
    void playerShow();
    void playerHide();

signals:
    void fire();
    void stopFiring();
    void dying();


private:
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    bool paused = false;
    QGraphicsScene *scene;
    Player *player;
    target *laserTarget;

    double targetedXCoord;
    double targetedYCoord;
    bool invincibility = false;
    const int startingLives = 4;

private slots:
    void refreshScene();
};

#endif // GAME_H
