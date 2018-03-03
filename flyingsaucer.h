#ifndef FLYINGSAUCER_H
#define FLYINGSAUCER_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QKeyEvent>


class Human;
class Spawner;
class FlyingSaucer: public QGraphicsRectItem
{
public:
    FlyingSaucer();
    void keyPressEvent(QKeyEvent* input);
    void SetSpawner(Spawner* s);
    Spawner* GetSpawner() const;

private:
    Spawner* spawner;
};

#endif // FLYINGSAUCER_H
