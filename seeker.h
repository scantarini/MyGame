#ifndef SEEKER_H
#define SEEKER_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>

class FlyingSaucer;
class Human;
class Seeker: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Seeker();
    void SetShip(FlyingSaucer* source);
public slots:
    void Move();
private:
    FlyingSaucer* motherShip;
};


#endif // SEEKER_H
