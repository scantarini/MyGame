#include "beam.h"
#include "human.h"
#include "seeker.h"
#include "flyingsaucer.h"

//Initializes the static member variables
QTimer Human::movementTimer;
QTimer Human::animationTimer;

// Constructor
Human::Human()
{
    /***************************************************
    * Sets the Human to start on the first frame of its animation
    * Sets the walk Direction randomly
    * Sets the human to be uncaught
    * Sets the starting image of the human
    * Sets the walk speed of the human
    * Sets the starting position of the human based
    *                         on the walk direction
    * Connects the movement and animation to timers
    ***************************************************/
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

    QObject::connect(&movementTimer, SIGNAL(timeout()), this, SLOT(Move()));
    movementTimer.start(20);
    QObject::connect(&animationTimer, SIGNAL(timeout()), this, SLOT(ChangeAnimation()));
    animationTimer.start(333);
}

// Associates human attributes to a beam if requested
Human::Human(Beam *beam)
{
    walkSpeed = -1;
    caught = true;
}

// Associates human attributes to a seeker if requested
Human::Human(Seeker *seeker)
{
    walkSpeed = -1;
    caught = true;
}

// Changes the walking direction of a human (when it hits the screen boundary)
void Human::ChangeWalkDirection()
{
    walkDirection = !walkDirection;
}

// Returns true if the human has been caught
bool Human::isCaught() const
{
    return caught;
}

// Sets the human to be caught
void Human::Caught()
{
    if(!GetSpeed()) return;
    caught = true;
}

// Returns the walking speed of the human
int Human::GetSpeed() const
{
    return walkSpeed;
}

// Sets the pointer to the flying saucer
void Human::SetMotherShip(FlyingSaucer *ship)
{
    motherShip = ship;
}

// Moves the human within the screen boundaries.
// When the boundary is hit, the direction is reversed if the flying saucer is not exiting.
// If the flying saucer is exiting, the human is removed via populationMaintenance
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
        if(!motherShip->IsLeaving())
            ChangeWalkDirection();
        else
        {
            Caught();
            motherShip->populationMaintenance();
        }

    }
}

// Updates the animation image of the human
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
