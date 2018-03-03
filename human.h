#ifndef HUMAN_H
#define HUMAN_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>

class Beam;
class Seeker;
class FlyingSaucer;
class Human: public QObject, public QGraphicsPixmapItem

{
    Q_OBJECT
public:
    Human();
    Human(Beam* beam);
    Human(Seeker* seeker);
    void ChangeWalkDirection();
    bool isCaught() const;
    void Caught();
    int GetSpeed() const;
    void SetMotherShip(FlyingSaucer* ship);
public slots:
    void Move();
    void ChangeAnimation();
private:
    int frameNumber;
    bool caught;
    bool walkDirection; // 0 for left, 1 for right
    int walkSpeed;
    int height;
    FlyingSaucer* motherShip;
};

#endif // HUMAN_H
