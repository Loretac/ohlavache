#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

/*********************************************************************
 **
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
