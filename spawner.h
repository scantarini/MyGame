#ifndef SPAWNER_H
#define SPAWNER_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>

class Spawner: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Spawner();
public slots:
    void spawnHuman();

};
#endif // SPAWNER_H
