#include "beam.h"
#include "human.h"
#include "seeker.h"
#include "flyingsaucer.h"


Beam::Beam()
{
    setPixmap(QPixmap(":/Models/capture2.png"));
    QTimer* timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start(13);
}

void Beam::SetShip(FlyingSaucer* source)
{
    motherShip = source;
}

void Beam::Move()
{
    bool caught = false;
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
    setPos(x(), y()+30);
    if(y()>595)
    {
        scene()->removeItem(this);
        delete this;
    }
    if(caught)
        motherShip->populationMaintenance();
}
