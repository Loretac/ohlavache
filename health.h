#ifndef HEALTH_H
#define HEALTH_H


#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{
public:
    // by default no parent for QGraphicsItem...here we choose to pass a parent
    Health(QGraphicsItem *parent = 0);
    void decrease();
    int getHealth();

private:
    int health;

};

#endif // HEALTH_H
