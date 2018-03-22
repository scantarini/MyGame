#ifndef LASER_H
#define LASER_Hd

#include <QGraphicsPixmapItem>
#include <QTimer>


// Forward declaration
class Giant;

// This is the projectile shot by the giant (UFO)
class Laser: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Laser(int x_pos, int y_pos, int x_speed, int y_speed); // Constructor
public slots:
    void Move(); // Controls the movement of the laser

private:
    int horizSpeed;         // The horizontal speed of a laser
    int vertSpeed;          // The vertical speed of a laser
    QTimer* movementTimer;  // Controls how often movement is updated for a laser
};

#endif // LASER_H
