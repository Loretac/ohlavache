#include "score.h"
#include <QFont>



/*********************************************************************
 ** Score constructor.
 *********************************************************************/
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

/*********************************************************************
 ** Increases the score.
 *********************************************************************/
void Score::increase()
{
    // increase the score
    score++;

    // update the text
    setPlainText(QString("Score: ") + QString::number(score));


}


/*********************************************************************
 ** Score getter.
 *********************************************************************/
int Score::getScore()
{
    return score;
}
