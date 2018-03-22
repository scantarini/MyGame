#include "gameender.h"

// Displays the exit button
GameEnder::GameEnder()
{
    setPixmap(QPixmap(":/Models/exit.png"));
    setPos(200,-200);
    this->hide();
}

// Emits that the exit button has been pressed
void GameEnder::mousePressEvent(QGraphicsSceneMouseEvent *click)
{
    emit clicked();
}

// Sets the exit button to the focused item (so that it can respond to a click)
void GameEnder::display()
{
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
    setPos(300,100);
    this->show();
}
