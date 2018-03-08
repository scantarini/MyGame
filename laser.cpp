#include "laser.h"

#include <QString>
#include <QGraphicsScene>

QString laserAnimation[15] =
{
    ":/Laser/Animation/Laser/00.gif",
    ":/Laser/Animation/Laser/01.gif",
    ":/Laser/Animation/Laser/02.gif",
    ":/Laser/Animation/Laser/03.gif",
    ":/Laser/Animation/Laser/04.gif",
    ":/Laser/Animation/Laser/05.gif",
    ":/Laser/Animation/Laser/06.gif",
    ":/Laser/Animation/Laser/07.gif",
    ":/Laser/Animation/Laser/08.gif",
    ":/Laser/Animation/Laser/09.gif",
    ":/Laser/Animation/Laser/10.gif",
    ":/Laser/Animation/Laser/11.gif",
    ":/Laser/Animation/Laser/12.gif",
    ":/Laser/Animation/Laser/13.gif",
    ":/Laser/Animation/Laser/14.gif"
};

Laser::Laser(int x_pos, int y_pos, int x_speed, int y_speed)
{
    setPixmap(QPixmap(":/Laser/Animation/Laser/00.gif"));
    setPos(x_pos, y_pos);
    horizSpeed = x_speed;
    vertSpeed = y_speed;
    animationPosition = 0;

    movementTimer = new QTimer;

    QObject::connect(movementTimer, SIGNAL(timeout()), this, SLOT(Move()));
    movementTimer->start(15);

    animationTimer = new QTimer;
    QObject::connect(animationTimer, SIGNAL(timeout()), this, SLOT(Animate()));
    animationTimer->start(1000);
}

void Laser::Move()
{
    setPos(x() + horizSpeed, y() + vertSpeed);
    if(y() > 800)
    {
        scene()->removeItem(this);
        movementTimer->stop();
        animationTimer->stop();
        QObject::disconnect(movementTimer, SIGNAL(timeout()), this, SLOT(Move()));
        QObject::disconnect(animationTimer, SIGNAL(timeout()), this, SLOT(Animate()));
        delete movementTimer;
        delete animationTimer;
        delete this;
    }
}

void Laser::Animate()
{
    setPixmap(QPixmap(laserAnimation[animationPosition]));
    ++animationPosition;
    if(animationPosition == 15) animationPosition = 0;
}
