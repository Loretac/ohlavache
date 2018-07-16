#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

/*********************************************************************
 ** Keeps track of the score. Hidden for now, may be used in later
 ** additions...
 *********************************************************************/

class Score: public QGraphicsTextItem{
public:
    // by default no parent for QGraphicsItem...here we choose to pass a parent
    Score(QGraphicsItem *parent = 0);
    void increase();
    int getScore();

private:
    int score;

};

#endif // SCORE_H
