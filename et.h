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
    virtual ~ET();
    void setMotherShip(FlyingSaucer* ship);
    void setAnimation();
    int GetHealth() const;
signals:
    void HealthChanged(int newHealth);
    void Destroyed();
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
    void CheckCollision();
    void StopMovement();
private:
    QTimer movementTimer;
    FlyingSaucer* motherShip;
    QString rightAnimation[20];
    QString leftAnimation[20];

    QTimer* collisionTimer;
    QTimer* testTimer;
    QTimer* shootingTimer;
    bool standingStill;
    bool walkDirection;
    bool lookingUp;
    QMediaPlayer fire;
    int health;
};


#endif // ET_H
