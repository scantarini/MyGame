#include "missile.h"
#include <QGraphicsScene>
#include "laser.h"
#include "giant.h"
#include "et.h"

QTimer Missile::movementTimer;
QTimer Missile::collisionTimer;

Missile::Missile(int dir)
{
    setZValue(5);
    QObject::connect(&collisionTimer, SIGNAL(timeout()), this, SLOT(CheckCollision()));
    // Direction 0 means left
    // Direction 1 means right
    // Direction 2 means up
    direction = dir;
    if(direction == 2)
    {
        setPixmap(QPixmap(":/Missile/Animation/Missile/shootup.png"));
        QObject::connect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveUp()));
    }
    else if(!direction)
    {
        setPixmap(QPixmap(":/Missile/Animation/Missile/shootleft.png"));
        QObject::connect(&Missile::movementTimer, SIGNAL(timeout()), this, SLOT(MoveLeft()));
    }
    else
    {
        setPixmap(QPixmap(":/Missile/Animation/Missile/shootright.png"));
        QObject::connect(&Missile::movementTimer, SIGNAL(timeout()), this, SLOT(MoveRight()));
    }
    if(!movementTimer.isActive())
    {
        movementTimer.start(15);
    }
    if(!collisionTimer.isActive())
    {
        collisionTimer.start(100);
    }
}

void Missile::MoveUp()
{
    setY(y()-15);
    if(y() < -100)
    {
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveUp()));
        scene()->removeItem(this);
        delete this;
    }
}

void Missile::MoveLeft()
{
    setX(x()-15);
    if(x() < -100)
    {
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveLeft()));
        scene()->removeItem(this);
        delete this;
    }
}

void Missile::MoveRight()
{
    setX(x()+15);

    if(x() > 1300)
    {
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveRight()));
        scene()->removeItem(this);
        delete this;
    }
}

void Missile::CheckCollision()
{
    QList<QGraphicsItem *> collisionList = collidingItems();
    foreach(QGraphicsItem* h, collisionList)
    {
        if(dynamic_cast<Laser*>(h))
        {
            scene()->removeItem(h);
            scene()->removeItem(this);
            delete h;
            delete this;
            return;
        }
        else if(dynamic_cast<Giant*>(h))
        {
            if(x() > 400 && x() < 930)
                dynamic_cast<Giant*>(h)->DecrementHealth();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
}
