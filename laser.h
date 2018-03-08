#ifndef LASER_H
#define LASER_H

#include <QGraphicsPixmapItem>
#include <QTimer>



class Giant;
class Laser: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Laser(int x_pos, int y_pos, int x_speed, int y_speed);
public slots:
    void Move();
    void Animate();

private:
    int horizSpeed;
    int vertSpeed;
    QTimer* movementTimer;
    QTimer* animationTimer;
    int animationPosition;

};

#endif // LASER_H
