#include "gameender.h"

GameEnder::GameEnder()
{
    setPixmap(QPixmap(":/Models/exit.png"));
    setPos(200,-200);
    this->hide();
}

void GameEnder::mousePressEvent(QGraphicsSceneMouseEvent *click)
{
    emit clicked();
}

void GameEnder::display()
{
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
    setPos(300,100);
    this->show();
}
