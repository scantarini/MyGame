#ifndef GIANT_H
#define GIANT_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QMediaPlayer>

// Forward declarations
class ET;
class Laser;

// This class implements the giant class (which shoots lasers and has an associated health)
class Giant: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Giant();                            // Constructor
    void SetET(ET* player);             // Allows the giant class to access the location to the player
    void DecrementHealth();             // Decreases the health of the giant (when it is his by a missile)
    void Initialize();                  // Initializes the member variables once the flying saucer is to enter the scene
    int GetHealth() const;              // Returns the health of the giant
    virtual ~Giant();                   // The (virtual) destructor
signals:
    void HealthChanged(int newHealth);  // Signals that the health has changed
    void Destroyed();                   // Signals that the health has reached 0
public slots:
    void Enter();                       // Enters the giant onto the screen and postpones its shooting action until it has entered completely.
    void Shoot();                       // Controls the giant shooting lasers
    void Animate();                     // Animates the giant
    void StartMusic();                  // Fades in new music while the giant is entering
private:
    int health;                         // The giant's health
    QTimer* giantTimer;                 // Controls the speed with which the giant enters the screen
    QTimer* animationTimer;             // Controls the animation speed of the giant
    QTimer* shootTimer;                 // Controls how quickly the giant shoots
    QTimer* musicTimer;                 // Controls the speed with which the music volume increases
    int animationPosition;              // Holds the position in the array of animation images (strings to their location in the resouce file)
    bool isEntered;                     // True if the giant has finished entering the screen
    ET* et;                             // A pointer to the player
    QMediaPlayer* music;                // A pointer to the media player that is in charge of playing the second song
};

#endif // GIANT_H
