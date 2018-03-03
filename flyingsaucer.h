#ifndef FLYINGSAUCER_H
#define FLYINGSAUCER_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <vector>


class Human;
class Spawner;
class FlyingSaucer: public QGraphicsRectItem
{
public:
    FlyingSaucer();
    void keyPressEvent(QKeyEvent* input);
    std::vector<Human*> population; // make this the live updater
};

#endif // FLYINGSAUCER_H
