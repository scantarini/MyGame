#ifndef BEAM_H
#define BEAM_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

class FlyingSaucer;
class Beam: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Beam();
    void SetShip(FlyingSaucer* source);
public slots:
    void Move();
private:
    FlyingSaucer* motherShip;
};


#endif // BEAM_H
