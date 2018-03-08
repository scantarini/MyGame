#ifndef FLYINGSAUCER_H
#define FLYINGSAUCER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QColor>
#include <QFont>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QKeyEvent>
#include <QTimer>
#include <QString>
#include <vector>

class Giant;
class Human;
class ET;
class FlyingSaucer: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    FlyingSaucer(QGraphicsTextItem* exit);
    Human* targetSlowestHuman();
    void keyPressEvent(QKeyEvent* input);
    void keyReleaseEvent(QKeyEvent* released);
    bool isLess(Human* &h1, Human* &h2);
    void populationInsert(Human* h);
    void populationMaintenance();
    void initializeAnimation();
    virtual ~FlyingSaucer();
    void setExitText(QGraphicsTextItem* exitText);
    void SetET(ET* player);
    bool IsLeaving() const;
public slots:
    void MakeHuman();
    void Animate();
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Leave();
private:
    QTimer time;
    QTimer animationTimer;
    QTimer spawnTimer;
    int seekerCounter;
    QMediaPlayer fire;
    std::vector<Human*> population; // make this the live updater
    QString animationSlides[24];
    QGraphicsTextItem* exitMessage;
    bool exitable;
    bool leaving;
    ET* et;
    QMediaPlayer* music;
};

#endif // FLYINGSAUCER_H
