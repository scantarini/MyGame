#include "missile.h"
#include <QGraphicsScene>

QTimer Missile::movementTimer;

Missile::Missile(int dir)
{
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
