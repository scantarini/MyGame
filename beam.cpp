#include "beam.h"
#include "flyingsaucer.h"


Beam::Beam()
{
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
    QList<QGraphicsItem *> collisionList = collidingItems();
    foreach(QGraphicsItem* h, collisionList)
    {
        // right here, check to see if there is a collision with a person
    }

    setPos(x(), y()+30);
    if(y()>595)
    {
        scene()->removeItem(this);
        delete this;
    }
}
