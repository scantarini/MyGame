#ifndef ET_H
#define ET_H


#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QString>
#include <QMediaPlayer>

class FlyingSaucer;
class ET: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ET();
    void setMotherShip(FlyingSaucer* ship);
    void setAnimation();

public slots:
    void keyPressEvent(QKeyEvent* input);
    void keyReleaseEvent(QKeyEvent* released);
    void AnimateLeft();
    void AnimateRight();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void StandStill();
private:
    QTimer movementTimer;
    FlyingSaucer* motherShip;
    QString rightAnimation[20];
    QString leftAnimation[20];

    QTimer* testTimer;
    QTimer* shootingTimer;
    bool standingStill;
    bool walkDirection;
    bool lookingUp;
    QMediaPlayer fire;
    int health;
};


#endif // ET_H
