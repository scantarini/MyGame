#ifndef MISSILE_H
#define MISSILE_H

#include <QTimer>
#include <QGraphicsPixmapItem>

class Missile: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Missile(int dir);
public slots:
    void MoveUp();
    void MoveLeft();
    void MoveRight();
    void CheckCollision();
private:
    int direction;
    static QTimer movementTimer;
    static QTimer collisionTimer;
};

#endif // MISSILE_H
