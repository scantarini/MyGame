#ifndef BEAM_H
#define BEAM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

class FlyingSaucer; // Forward declaration of the FlyingSaucer class

/**********************************************************************
    Beam Class:
    This class is a projectile fired by the player FlyingSaucer.
    This particular projectile moves up and down and only destructs
    when it leaves the screen or collides with one or more humans.
**********************************************************************/
class Beam: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Beam();
    void SetShip(FlyingSaucer* source); //  Gives a beam object a reference to the FlyingSaucer (that it was shot from).
public slots:
    void Move(); // Moves the beam downward.
private:
    FlyingSaucer* motherShip; // The reference to the FlyingSaucer from which the Beam was shot
};


#endif // BEAM_H
