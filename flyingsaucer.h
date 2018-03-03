#ifndef FLYINGSAUCER_H
#define FLYINGSAUCER_H

#include <QGraphicsRectItem>
#include <QKeyEvent>


class Human;
class Spawner;
class FlyingSaucer: public QGraphicsRectItem
{
public:
    FlyingSaucer();
    void keyPressEvent(QKeyEvent* input);
};

#endif // FLYINGSAUCER_H
