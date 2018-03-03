#ifndef HUMAN_H
#define HUMAN_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>

class Beam;
class Human: public QObject, public QGraphicsPixmapItem

{
    Q_OBJECT
public:
    Human();
    Human(Beam* beam);
    int GetSpeed() const;
public slots:
    void Move();
private:
    bool walkDirection; // 0 for left, 1 for right
    int walkSpeed;
    int height;
};

#endif // HUMAN_H
