#ifndef FLYINGSAUCER_H
#define FLYINGSAUCER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QColor>
#include <QFont>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QKeyEvent>
#include <QTimer>
#include <QString>
#include <vector>

//Forward declarations
class Giant;
class Human;
class ET;

// This class implements the flying saucer (that the player controls when the game starts)
class FlyingSaucer: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    FlyingSaucer(QGraphicsTextItem* exit);                      // Constructor that processes the message that prompts the player to exit the ship
    Human* targetSlowestHuman();                                // Returns the position of the human with the slowest walkingSpeed
    void keyPressEvent(QKeyEvent* input);                       // Processes key inputs
    void keyReleaseEvent(QKeyEvent* released);                  // Processes key releases
    bool isLess(Human* &h1, Human* &h2);                        // Returns true if the walking speed of h1 is less than that of h2 (false otherwise)
    void populationInsert(Human* h);                            // Inserts a human into the population vector
    void populationMaintenance();                               // Removes all humans from the population vector that have been captured
    void initializeAnimation();                                 // Initializes the array of animation slides
    virtual ~FlyingSaucer();                                    // (virtual) destructor
    void setExitText(QGraphicsTextItem* exitText);              // Initializes the screen message (that tells the player how to exit the ship)
    void SetET(ET* player);                                     // Allows the FlyingSaucer to access the player ET
    bool IsLeaving() const;                                     // Returns the leaving boolean variable. (The flying saucer leaves when the player exits)
    void SetGiant(Giant* g);                                    // Allows the FlyingSaucer to add the giant (giant UFO) to the scene
signals:
    void ETVisible();                                           //  Tells the program to display the ET
public slots:
    void MakeHuman();                                           // Spawns a human and adds it to the scene
    void Animate();                                             // Changes the animation image (animates the flying saucer)
    void MoveUp();                                              // Moves the flying saucer up
    void MoveDown();                                            // Moves the flying saucer down
    void MoveLeft();                                            // Moves the flying saucer left
    void MoveRight();                                           // Moves the flying saucer right
    void Leave();                                               // Moves the flying saucer up until there are no more humans
                                                                // Then it tells the giant to enter the screen
private:
    QTimer time;                                                // Sets the rate at which movement of the flying saucer takes place
    QTimer animationTimer;                                      // Sets the speed of the animation image updating
    QTimer spawnTimer;                                          // Sets the frequency at which humans are spawned
    int seekerCounter;                                          // Stores the number of seekers currently on the screen
    QMediaPlayer fire;                                          // In charge of playing the fire sound
    std::vector<Human*> population;                             // A vector of pointers to all the humans on the screen
    QString animationSlides[24];                                // An array of animation images (strings to their locations)
    QGraphicsTextItem* exitMessage;                             // A pointer to the text message (that would tell the player how to exit the ship)
    bool exitable;                                              // When the flying saucer is exitable, the shift key will exit the player from the ship
    bool leaving;                                               // True if the player has exited the flying saucer (which triggers the ship to leave)
    ET* et;                                                     // A pointer to the humanoid form that the player plays as
    Giant* giant;                                               // A pointer to the giant (UFO) that enters when the flying saucer leaves
    QMediaPlayer* music;                                        // Accesses the background music (so that it can fade it out as the ship exits)
};

#endif // FLYINGSAUCER_H
