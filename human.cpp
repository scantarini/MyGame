#include "beam.h"
#include "human.h"


Human::Human()
{
    setPixmap(QPixmap(":/Models/Character.png"));
    walkSpeed = rand()%5 + 5;
    walkDirection = rand()%2;
    if(walkDirection == 1)
        setPos(0,575);
    else if (walkDirection == 0)
    {
        setPos(1280,575);
    }

    QTimer* timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start(20);
}

Human::Human(Beam *beam)
{
    walkSpeed = 0;
}

int Human::GetSpeed() const
{
    return walkSpeed;
}

void Human::Move()
{
    if(walkDirection)
        setPos(x()+walkSpeed, y());
    else
    {
        setPos(x()-walkSpeed,y());
    }

    if(x() > 1280 || x() < 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
