#include "beam.h"
#include "flyingsaucer.h"
#include "human.h"


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
        if(h!=motherShip)
        {
            scene()->removeItem(dynamic_cast<Human*>(h));
            delete h;
        }
    }

    setPos(x(), y()+30);
    if(y()>595)
    {
        scene()->removeItem(this);
        delete this;
    }
}
