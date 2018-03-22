#include "flyingsaucer.h"
#include "human.h"
#include "beam.h"
#include "seeker.h"

// Constructor
Seeker::Seeker()
{
    /*
    * Initialize caught to false (since each seeker can only catch one human)
    * Set the image for the seeker
    * Connect the movement of the seeker to a timer
    */
    caught = false;
    setPixmap(QPixmap(":/Models/capture2.png"));
    QTimer* timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start(15);
}

// Set the pointer to the flying saucer
void Seeker::SetShip(FlyingSaucer* source)
{
    motherShip = source;
}

// Controls the movement of the seeker
void Seeker::Move()
{
    bool captured = false;
    Human* h = motherShip->targetSlowestHuman(); // finds the slowest human

    // Moves the seeker toward the slowest human
    if(h!=nullptr)
    {
        setPos((39*x() + h->x())/40, (39*y() + h->y())/40);
    }

    // Runs through the list of items that the seeker collides with
    QList<QGraphicsItem *> collisionList = collidingItems();
    if(!collidingItems().empty())
    foreach(QGraphicsItem* a, collidingItems())
    {
        if(a == h) // if colliding with the slowest human, set that human as captured
        {
           captured = true;
           h->Caught();
           break;
        }
    }

    // move the seeker down by 1
    setPos(x(), y()+1);

    // Remove the seeker if it hits the ground
    if(y()>570)
    {
        scene()->removeItem(this);
        delete this;
    }

    // If the seeker caught the slowest human, remove it from the population vector (in the flying saucer class) via populationMaintenance
    if(captured)
        motherShip->populationMaintenance();
}
