#ifndef MISSILE_H
#define MISSILE_H

#include <QTimer>
#include <QGraphicsPixmapItem>

// This is the projectile shot by the player (after exiting the ship)
class Missile: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Missile(int dir); // Constructor (with an associated direction)
public slots:
    void MoveUp();          // Moves a missile upward
    void MoveLeft();        // Moves a missile left
    void MoveRight();       // Moves a missile right
    void CheckCollision();  // Checks to see if there is a collision with a laser or with the giant (UFO)
private:
    int direction;                  // The missile's moving direction
    static QTimer movementTimer;    // Controls how often a missile's movement updates
    static QTimer collisionTimer;   // Controls how often a missile checks for collisions
};

#endif // MISSILE_H
