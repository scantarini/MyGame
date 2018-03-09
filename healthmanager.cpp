#include "healthmanager.h"
#include "et.h"
#include "giant.h"
#include "gameender.h"
#include <QApplication>
HealthManager::HealthManager(ET* player, QGraphicsTextItem* playerText, Giant* giant, QGraphicsTextItem* giantText, GameEnder* button)
{
    btn = button;
    etPtr = player;
    giantPtr = giant;
    giantMessage = giantText;
    etMessage = playerText;
}

void HealthManager::updatePlayerDisplay(int playerHealth)
{
    if(etPtr->isVisible())
        etMessage->setPlainText("Player Health: " + QString::number(etPtr->GetHealth()));
}

void HealthManager::updateGiantDisplay(int giantHealth)
{
    if(giantPtr->isVisible())
        giantMessage->setPlainText("Giant Health: " + QString::number(giantPtr->GetHealth()));
}

void HealthManager::DisplaySetup()
{
    etMessage->setPlainText("Player Health: " + QString::number(100));
    giantMessage->setPlainText("Giant Health: " + QString::number(100));
}

void HealthManager::GameOver()
{
    etMessage->setPlainText("GAME OVER");
    giantMessage->setPlainText("");
    emit EndSignal();
}
