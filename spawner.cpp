#include "spawner.h"
#include "human.h"
#include <QDebug>

Spawner::Spawner()
{
    QTimer* timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(spawnHuman()));
    timer->start(100);
}

void Spawner::spawnHuman()
{
    if(rand()%100 < 10)
    {
        Human* human = new Human();
        human->setParentItem(this);
    }

    QList<QGraphicsItem *> h = this->childItems();
}

