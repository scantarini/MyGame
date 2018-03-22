#include "beam.h"
#include "human.h"
#include "seeker.h"
#include "flyingsaucer.h"

// constructor
Beam::Beam()
{
    // Initializes the beam's image and connects a beam's movement to a timer
    setPixmap(QPixmap(":/Models/capture2.png"));
    QTimer* timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start(13);
}

// Sets the flying saucer pointer
void Beam::SetShip(FlyingSaucer* source)
{
    motherShip = source;
}

// Controls the beam movement
void Beam::Move()
{
    bool caught = false;

    // Checks all collisions to see if a beam is colliding with a human
    QList<QGraphicsItem *> collisionList = collidingItems();
    foreach(QGraphicsItem* h, collisionList)
    {
        if(h == motherShip) continue;
        if(dynamic_cast<Seeker*>(h)) continue;

        if(dynamic_cast<Human*>(h)->GetSpeed()>0)
        {
            dynamic_cast<Human*>(h)->Caught();
            caught = true;
        }
    }

    // Responsible for the downward movement of the beam
    setPos(x(), y()+30);
    if(y()>595)
    {
        scene()->removeItem(this);
        delete this;
    }

    // Removes humans from the population vector (in the FlyingSaucer class) that have been caught
    if(caught)
        motherShip->populationMaintenance();
}
