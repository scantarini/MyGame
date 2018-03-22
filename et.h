#ifndef ET_H
#define ET_H


#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QString>
#include <QMediaPlayer>

class FlyingSaucer;                             // Forward Declaration of the FlyingSaucer class

class ET: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ET();                                       // Constructor
    virtual ~ET();                              // (Virtual) Destructor
    void setMotherShip(FlyingSaucer* ship);     // Gives the ET a reference to the FlyingSaucer
    void setAnimation();                        // Initializes the array of animation images
    int GetHealth() const;                      // Returns the health of the player
signals:
    void HealthChanged(int newHealth);          // Signals that the player's health has changed (hit by a laser)
    void Destroyed();                           // Signals that the player's health has hit 0
public slots:
    void keyPressEvent(QKeyEvent* input);       // Processes keyboard input for moving, shooting, and looking up
    void keyReleaseEvent(QKeyEvent* released);  // Processes keyboard input for when a key is released
    void AnimateLeft();                         // Sets the animation slides to the left-running slides
    void AnimateRight();                        // Sets the animation slides to the right-running slides
    void MoveLeft();                            // Moves the player left (when the 'a' key is pressed)
    void MoveRight();                           // Moves the player right (when the 'd' key is pressed)
    void MoveUp();                              // A holder for if jump functionality would be built in
    void MoveDown();                            // A holder for if a ducking functionality would be built in
    void StandStill();                          // Sets the animation image to the standing-still image
    void CheckCollision();                      // Checks to see if the ET is colliding (with a laser)
    void StopMovement();                        // Stops all timers
private:
    QTimer movementTimer;                       // Controls the speed of the player movement in some direction
    FlyingSaucer* motherShip;                   // A pointer to the FlyingSaucer the player exited
    QString rightAnimation[20];                 // The anmiation images for the player running right
    QString leftAnimation[20];                  // The animation images for the player running left

    QTimer* collisionTimer;                     // Sets a time interval for how often collision is checked (with a laser)
    QTimer* testTimer;                          // This timer fixes the following problem:
                                                // Holding down a key isn't a continuous input. Rather, holding a key down
                                                // just presses a key very fast (often). This made the problem that the key
                                                // was released and pressed very quickly. So the animation would switch between
                                                // moving and standing still very quickly.

    QTimer* shootingTimer;                      // Sets a limit to how often the player can shoot
    bool standingStill;                         // A boolean that is true if the player is standing still
    bool walkDirection;                         // 0 (false) means the player is facing left. 1 (right) means the player is facing right
    bool lookingUp;                             // 0 if the player is not looking up. 1 if the player is looking up
    QMediaPlayer fire;                          // This is in charge of playing the shooting sound
    int health;                                 // The player health
};


#endif // ET_H
