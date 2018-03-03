#ifndef FLYINGSAUCER_H
#define FLYINGSAUCER_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QTimer>
#include <QString>
#include <vector>



class Human;
//class Spawner;
class FlyingSaucer: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    FlyingSaucer();
    Human* targetSlowestHuman();
    void keyPressEvent(QKeyEvent* input);
    void keyReleaseEvent(QKeyEvent* released);
    bool isLess(Human* &h1, Human* &h2);
    void populationInsert(Human* h);
    void populationMaintenance();
    void initializeAnimation();
    virtual ~FlyingSaucer();
public slots:
    void MakeHuman();
    void Animate();
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
private:
    QTimer time;
    QTimer animationTimer;
    QTimer spawnTimer;
    int seekerCounter;
    QMediaPlayer fire;
    std::vector<Human*> population; // make this the live updater
    QString animationSlides[24];
};

#endif // FLYINGSAUCER_H
