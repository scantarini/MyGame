#include "laser.h"

#include <QString>
#include <QGraphicsScene>

// Constructor
Laser::Laser(int x_pos, int y_pos, int x_speed, int y_speed)
{
    /***************************************************
    * Sets the ZValue to 4
    * Sets the starting image
    * Sets the initial position and speed
    * Connects the movement to a timer
    ***************************************************/
    setZValue(4);
    setPixmap(QPixmap(":/Laser/Animation/Laser/00.gif"));
    setPos(x_pos, y_pos);
    horizSpeed = x_speed;
    vertSpeed = y_speed;

    movementTimer = new QTimer;

    QObject::connect(movementTimer, SIGNAL(timeout()), this, SLOT(Move()));
    movementTimer->start(15);
}

// Moves the laser based on its position and speed
void Laser::Move()
{
    setPos(x() + horizSpeed, y() + vertSpeed);

    // Deletes the laser when it leaves the screen boundary
    if(y() > 800)
    {
        scene()->removeItem(this);
        movementTimer->stop();
        QObject::disconnect(movementTimer, SIGNAL(timeout()), this, SLOT(Move()));
        delete movementTimer;
        delete this;
    }
}
