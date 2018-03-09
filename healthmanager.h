#ifndef HEALTHMANAGER_H
#define HEALTHMANAGER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QString>
#include <QTimer>

class Giant;
class ET;
class GameEnder;
class HealthManager: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    HealthManager(ET* player, QGraphicsTextItem* playerText, Giant* giant, QGraphicsTextItem* giantText, GameEnder* button);
public slots:
    void updatePlayerDisplay(int playerHealth);
    void updateGiantDisplay(int giantHealth);
    void DisplaySetup();
    void GameOver();
signals:
    void EndSignal();
private:
    QString health;
    QString enemyHealth;
    QGraphicsTextItem* giantMessage;
    QGraphicsTextItem* etMessage;
    ET* etPtr;
    Giant* giantPtr;
    QPushButton end;
    GameEnder* btn;
};
#endif // HEALTHMANAGER_H
