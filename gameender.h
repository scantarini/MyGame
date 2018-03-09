#ifndef GAMEENDER_H
#define GAMEENDER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
class GameEnder: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameEnder();
    void mousePressEvent(QGraphicsSceneMouseEvent* click);
public slots:
    void display();
signals:
    void clicked();
private:
};
#endif // GAMEENDER_H
