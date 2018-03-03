#include "flyingsaucer.h"
#include "human.h"
#include "beam.h"
#include "seeker.h"


Seeker::Seeker()
{
    caught = false;
    setPixmap(QPixmap(":/Models/capture2.png"));
    QTimer* timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start(15);
}

void Seeker::SetShip(FlyingSaucer* source)
{
    motherShip = source;
}

void Seeker::Move()
{
    bool captured = false;
    Human* h = motherShip->targetSlowestHuman();
    if(h!=nullptr)
    {
        setPos((39*x() + h->x())/40, (39*y() + h->y())/40);
    }
    QList<QGraphicsItem *> collisionList = collidingItems();
    if(!collidingItems().empty())
    foreach(QGraphicsItem* a, collidingItems())
    {
        if(a == h)
        {
           captured = true;
           h->Caught();
           break;
        }
    }

    setPos(x(), y()+1);
    if(y()>570)
    {
        scene()->removeItem(this);
        delete this;
    }

    if(captured)
        motherShip->populationMaintenance();
}
