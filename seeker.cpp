#include "flyingsaucer.h"
#include "human.h"
#include "seeker.h"
#include "spawner.h"


Seeker::Seeker()
{
    setRect(0,0,20,20);
    QTimer* timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start(13);
}

void Seeker::SetShip(FlyingSaucer* source)
{
    motherShip = source;
}

#include <QDebug>
void Seeker::Move()
{
    QList<QGraphicsItem *> humanList = motherShip->GetSpawner()->childItems();
    foreach(QGraphicsItem* h, humanList)
    {
        if(h!=motherShip && dynamic_cast<Human*>(h)->GetSpeed() != 0)
        {
            setPos((29*x() + h->x())/30, (29*y() + h->y())/30);
            break;
        }
    }

    QList<QGraphicsItem *> collisionList = collidingItems();
    foreach(QGraphicsItem* h, collidingItems())
    {
        if(h!=motherShip && !dynamic_cast<Seeker*>(h))
        {
            scene()->removeItem(dynamic_cast<Human*>(h));
            delete h;
        }
    }

    setPos(x(), y()+1);
    if(y()>595)
    {
        scene()->removeItem(this);
        delete this;
    }
}
