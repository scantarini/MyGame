#include "beam.h"
#include "human.h"
#include "seeker.h"
#include "flyingsaucer.h"


Human::Human()
{
    frameNumber = 0;
    walkDirection = rand()%2;
    caught = false;
    if(walkDirection)
        setPixmap(QPixmap(":/MarioRight/Animation/MarioRightFrames/Frame0.gif"));
    else
        setPixmap(QPixmap(":/MarioRight/Animation/MarioLeftFrames/Frame0.gif"));

    walkSpeed = rand()%5 + 5;
    if(walkDirection == 1)
        setPos(0,575);
    else if (walkDirection == 0)
    {
        setPos(1280,575);
    }

    QTimer* timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start(20);
    QTimer* timer2 = new QTimer;
    QObject::connect(timer2, SIGNAL(timeout()), this, SLOT(ChangeAnimation()));
    timer2->start(333);
}

Human::Human(Beam *beam)
{
    walkSpeed = -1;
    caught = true;
}

Human::Human(Seeker *seeker)
{
    walkSpeed = -1;
    caught = true;
}

void Human::ChangeWalkDirection()
{
    walkDirection = !walkDirection;
}

bool Human::isCaught() const
{
    return caught;
}

void Human::Caught()
{
    if(!GetSpeed()) return;
    caught = true;
}

int Human::GetSpeed() const
{
    return walkSpeed;
}

void Human::SetMotherShip(FlyingSaucer *ship)
{
    motherShip = ship;
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
        ChangeWalkDirection();
    }
}

void Human::ChangeAnimation()
{
    if(walkDirection)
    {
        if(frameNumber%3 == 0) setPixmap(QPixmap(":/MarioRight/Animation/MarioRightFrames/Frame0.gif"));
        else if(frameNumber%3 == 1) setPixmap(QPixmap(":/MarioRight/Animation/MarioRightFrames/Frame1.gif"));
        else if(frameNumber%3 == 2) setPixmap(QPixmap(":/MarioRight/Animation/MarioRightFrames/Frame0.gif"));
    }
    else if(walkDirection == 0)
    {
        if(frameNumber%3 == 0) setPixmap(QPixmap(":/MarioLeft/Animation/MarioLeftFrame/Frame0.gif"));
        else if(frameNumber%3 == 1) setPixmap(QPixmap(":/MarioLeft/Animation/MarioLeftFrame/Frame1.gif"));
        else if(frameNumber%3 == 2) setPixmap(QPixmap(":/MarioLeft/Animation/MarioLeftFrame/Frame2.gif"));
    }
    frameNumber++;
}
