#ifndef SEEKER_H
#define SEEKER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <queue>

class FlyingSaucer;
class Human;
class Seeker: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Seeker();
    void SetShip(FlyingSaucer* source);
    void Caught();
    void HasCaught();
public slots:
    void Move();
private:
    bool caught;
    FlyingSaucer* motherShip;
};


#endif // SEEKER_H
