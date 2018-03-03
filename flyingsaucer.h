#ifndef FLYINGSAUCER_H
#define FLYINGSAUCER_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <vector>


class Human;
class Spawner;
class FlyingSaucer: public QGraphicsPixmapItem
{
public:
    FlyingSaucer();
    void keyPressEvent(QKeyEvent* input);
    void SetSpawner(Spawner* s);
    Spawner* GetSpawner() const;

private:
    Spawner* spawner;
    QMediaPlayer* fire;
    std::vector<Human*> population; // make this the live updater
};

#endif // FLYINGSAUCER_H
