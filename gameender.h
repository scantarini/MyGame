#ifndef GAMEENDER_H
#define GAMEENDER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

// This is the exit button that ends the program when it is clicked
class GameEnder: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameEnder();
    void mousePressEvent(QGraphicsSceneMouseEvent* click);  // Tells the program that the button was clicked (so the program should end)
public slots:
    void display();                                         // Displays the exit button when the player or giant health reach 0
signals:
    void clicked();                                         // Ends the program
private:
};
#endif // GAMEENDER_H
