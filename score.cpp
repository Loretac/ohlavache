#include "score.h"
#include <QFont>




Score::Score(QGraphicsItem *parent)
{
    // initialize score to zero
    score = 0;

    // draw the text
    //convert to string...
    setPlainText(QString("Score: ") + QString::number(score));

    setDefaultTextColor(Qt::blue); // make text blue
    setFont(QFont("times", 16)); // font family and size

}


void Score::increase()
{
    // increase the score
    score++;

    // update the text
    setPlainText(QString("Score: ") + QString::number(score));


}



int Score::getScore()
{
    return score;
}
