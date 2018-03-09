#ifndef LASER_H
#define LASER_Hd

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

private:
    int horizSpeed;
    int vertSpeed;
    QTimer* movementTimer;

};

#endif // LASER_H
