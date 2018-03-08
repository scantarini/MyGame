#ifndef GIANT_H
#define GIANT_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QMediaPlayer>

class ET;
class Laser;
class Giant: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Giant();
    void SetET(ET* player);
    virtual ~Giant();
public slots:
    void Enter();
    void Shoot();
    void Animate();
    void StartMusic();
private:
    int health;
    QTimer* giantTimer;
    QTimer* animationTimer;
    QTimer* shootTimer;
    QTimer* musicTimer;
    int animationPosition;
    bool isEntered;
    ET* et;
    QMediaPlayer* music;
};

#endif // GIANT_H
