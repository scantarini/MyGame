#ifndef ET_H
#define ET_H


#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QString>

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
    bool standingStill;
    bool walkDirection;
    bool lookingUp;

};


#endif // ET_H
