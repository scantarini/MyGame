#include "healthmanager.h"
#include "et.h"
#include "giant.h"
#include "gameender.h"
#include <QApplication>

// Initializes the messages that display the player and giant health and gets a pointer to the exit button.
HealthManager::HealthManager(ET* player, QGraphicsTextItem* playerText, Giant* giant, QGraphicsTextItem* giantText, GameEnder* button)
{
    btn = button;
    etPtr = player;
    giantPtr = giant;
    giantMessage = giantText;
    etMessage = playerText;
}

// Changes the ET (player) health message (when the ET health changes)
void HealthManager::updatePlayerDisplay(int playerHealth)
{
    if(etPtr->isVisible())
        etMessage->setPlainText("Player Health: " + QString::number(etPtr->GetHealth()));
}

// Changes the giant health message (when the giant health changes)
void HealthManager::updateGiantDisplay(int giantHealth)
{
    if(giantPtr->isVisible())
        giantMessage->setPlainText("Giant Health: " + QString::number(giantPtr->GetHealth()));
}

// Initializes the player and giant health messages
void HealthManager::DisplaySetup()
{
    etMessage->setPlainText("Player Health: " + QString::number(100));
    giantMessage->setPlainText("Giant Health: " + QString::number(100));
}

// Displays a game over message and signals for the exit button to display
void HealthManager::GameOver()
{
    etMessage->setPlainText("GAME OVER");
    giantMessage->setPlainText("");
    emit EndSignal();
}
