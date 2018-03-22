#ifndef SEEKER_H
#define SEEKER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <queue>

// Forward Declarations
class FlyingSaucer;
class Human;

// This is the projectile shot by the flying saucer (player) that targets the slowest-moving human on the screen
class Seeker: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Seeker();                           // Constructor
    void SetShip(FlyingSaucer* source); // Sets the pointer to the flying saucer (that the seeker is shot from)
    void Caught();                      // Sets the caught private member when the seeker catches a human.
                                        // This is because a seeker can only catch one human.
public slots:
    void Move();                        // Moves the seeker toward the slowest moving human
private:
    bool caught;                        // Boolean telling whether or not a seeker has caught a human
    FlyingSaucer* motherShip;           // Pointer to the flying saucer
};


#endif // SEEKER_H
