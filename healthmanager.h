#ifndef HEALTHMANAGER_H
#define HEALTHMANAGER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QString>
#include <QTimer>

// Forward Declarations
class Giant;
class ET;
class GameEnder;

// Manages the health display for both the player and the giant
class HealthManager: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    HealthManager(ET* player, QGraphicsTextItem* playerText, Giant* giant, QGraphicsTextItem* giantText, GameEnder* button); // constructor
public slots:
    void updatePlayerDisplay(int playerHealth); // Changes the display of the player health when the player health changes
    void updateGiantDisplay(int giantHealth);   // Changes the display of the giant health when the giant health changes
    void DisplaySetup();                        // Initializes the player and giant health status to 100
    void GameOver();                            // Displays a game over message when the giant or player health reaches 0
signals:
    void EndSignal();                           // Signals used to trigger the exit button to display
private:
    QString health;                             // String for the player health message
    QString enemyHealth;                        // String for the giant health message
    QGraphicsTextItem* giantMessage;            // Text item that is added to the QGraphicsScene (display for giant health)
    QGraphicsTextItem* etMessage;               // Text item that is added to the QGraphicsScene (display for player health)
    ET* etPtr;                                  // A pointer to the ET (player) for accessing the player health as it changes
    Giant* giantPtr;                            // A pointer to the giant for accessing the giant health as it changes
    GameEnder* btn;                             // The exit button
};
#endif // HEALTHMANAGER_H
