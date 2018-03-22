#ifndef HUMAN_H
#define HUMAN_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>

// Forward declarations
class Beam;
class Seeker;
class FlyingSaucer;

// This class is for controling the human characters (mario characters)
class Human: public QObject, public QGraphicsPixmapItem

{
    Q_OBJECT
public:
    Human();                                // Constructor
    Human(Beam* beam);                      // Constructor to handle beams
    Human(Seeker* seeker);                  // Constructor to handle seekers
    void ChangeWalkDirection();             // Changes the direction a human walks
    bool isCaught() const;                  // Checks to see if a human has been caught by the flying saucer
    void Caught();                          // Marks the human as caught if it has come in contact with a beam or a seeker
    int GetSpeed() const;                   // Returns a human's walking speed
    void SetMotherShip(FlyingSaucer* ship); // Sets the motherShip pointer
public slots:
    void Move();                            // Moves the human based on walking speed and direction
    void ChangeAnimation();                 // Updates the image for a human's animation
private:
    int frameNumber;                        // The position in the animation image array (which just contains strings to the image locations)
    bool caught;                            // Stores whether or not a player has been caught by the flying saucer
    bool walkDirection;                     // The walking direction: 0 for left, 1 for right
    int walkSpeed;                          // Walking speed for a human
    FlyingSaucer* motherShip;               // A pointer to the flying saucer
    static QTimer movementTimer;            // The rate at which movement updates for the humans
    static QTimer animationTimer;           // The rate at which the animation changes for the humans
};

#endif // HUMAN_H
