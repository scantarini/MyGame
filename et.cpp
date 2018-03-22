#include "et.h"
#include "missile.h"
#include <QGraphicsScene>
#include "laser.h"

// This class is for the player after exiting the flying saucer
ET::ET()
{
    // Initializes the animation images and sets the starting image
    setAnimation();
    setPixmap(QPixmap(":/Models/standing4.png"));

    // Assigns variables that contribute to the player's movement
    health = 100;
    walkDirection = 0;
    standingStill = true;
    lookingUp = false;

    // Sets the location for the audio file for the firing sound (shooting missiles)
    fire.setMedia(QUrl("qrc:/Music/cannon.wav"));

    // Sets timers that control how often collisions are checked, sets a limit on how often missiles can be fired
    // and sets a timer to make movement smooth.
    collisionTimer = new QTimer;
    shootingTimer = new QTimer;
    testTimer = new QTimer;

    // Sets the two timers to single shot (so they tick once then stop)
    shootingTimer->setSingleShot(true);
    testTimer->setSingleShot(true);

    // Connects timers to their corresponding actions
    QObject::connect(collisionTimer, SIGNAL(timeout()), this, SLOT(CheckCollision()));
    QObject::connect(testTimer, SIGNAL(timeout()), this, SLOT(StandStill()));
    collisionTimer->start(100);
    movementTimer.start(20);

}

ET::~ET()
{
    // Deletes the dynamically-allocated timers
    delete collisionTimer;
    delete testTimer;
    delete shootingTimer;
}

// Sets the pointer to the flying saucer
void ET::setMotherShip(FlyingSaucer *ship)
{
    motherShip = ship;
}

// Controls the player's movement
void ET::keyPressEvent(QKeyEvent *input)
{
    /*
    * W - Look up
    * D - Move right
    * A - Move left
    * Space - Fire missile
    */
    if(!lookingUp && input->key() == Qt::Key_A)
    {
        walkDirection = 0; // Walk left
        QObject::connect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveLeft()));
        QObject::connect(&movementTimer, SIGNAL(timeout()), this, SLOT(AnimateLeft()));

    }
    else if(!lookingUp && input->key() == Qt::Key_D)
    {
        walkDirection = 1; // Walk right
        QObject::connect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveRight()));
        QObject::connect(&movementTimer, SIGNAL(timeout()), this, SLOT(AnimateRight()));
    }
    else if(input->key()==Qt::Key_W)
    {
        // Aims up
        if(walkDirection)
            setPixmap(QPixmap(":/Models/aimingupright2.png"));
        else
            setPixmap(QPixmap(":/Models/aimingupleft2.png"));
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveLeft()));
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(AnimateLeft()));
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveRight()));
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(AnimateRight()));
        lookingUp = true;
    }
    else if(!shootingTimer->isActive() && input->key()==Qt::Key_Space)
    {
        // Resets the audio for firing a missile if it is currently playing and resets the audio to play from the beginning
        if(fire.state() == QMediaPlayer::PlayingState)
            fire.setPosition(0);
        else
            fire.play();

        // Creates a missile and adds it to the scene based on which direction the player is facing (including upwards)
        Missile* missile;
        if(lookingUp)
        {
            missile = new Missile(2);
            if(walkDirection)
                missile->setPos(x()+50, y()-50);
            else
                missile->setPos(x()+45, y() -50);
        }
        else if(walkDirection)
        {
            missile = new Missile(1);
            missile->setPos(x()+85, y()+48);
        }
        else
        {
            missile = new Missile(0);
            missile->setPos(x()-20, y()+48);
        }
        scene()->addItem(missile);
        shootingTimer->start(100); // Allows the player to shoot a missile once every 100 milliseconds
    }
    standingStill = false;
    testTimer->start(200); // This makes the running animation smooth.
                           // Before this was added, there was very rapid reset of the player to the stand-still animation.
                           // This is because when holding a key, it is just pressed very quickly, so there were many key releases.
}

// Handles the actions when a key is released
void ET::keyReleaseEvent(QKeyEvent *released)
{
    // The same control scheme as in the keyPressEvent
    if(released->key() == Qt::Key_W)
    {
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveUp()));
        lookingUp = false;
    }
    else if(released->key() == Qt::Key_S)
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveDown()));
    else if(released->key() == Qt::Key_A)
    {
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveLeft()));
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(AnimateLeft()));
    }
    else if(released->key() == Qt::Key_D)
    {
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveRight()));
        QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SIGNAL(AnimateRight()));
    }
    if(!testTimer->isActive()) // Does not return to the stand-still animation until all movement has ceased for 200 milliseconds.
        testTimer->start(200);
}

// Animates the player to run left (on a timer)
void ET::AnimateLeft()
{
    static int i = 0;
    setPixmap(QPixmap(leftAnimation[i]));
    ++i;
    if(i==20) i = 0;
}

// Animates the player to run right (on a timer)
void ET::AnimateRight()
{
    static int i = 0;
    setPixmap(QPixmap(rightAnimation[i]));
    ++i;
    if(i == 20) i = 0;
}

// Moves the player left
void ET::MoveLeft()
{
    if(x()>10)
        setPos(x()-15, y());
}

// Moves the player right
void ET::MoveRight()
{
    if(x()<1090)
        setPos(x()+15, y());
}

// Jump (may be added later)
void ET::MoveUp()
{
}

// Roll (may be added later)
void ET::MoveDown()
{}

// Sets the player character to a stand-still image
void ET::StandStill()
{
    if(!standingStill && !lookingUp && !testTimer->isActive())
    {
        if(walkDirection)
            setPixmap(QPixmap(":/Models/standing5.png"));
        else
            setPixmap(QPixmap(":/Models/standingleft.png"));
    }
}

// Detects collisions with lasers fired by the giant (UFO)
void ET::CheckCollision()
{
    QList<QGraphicsItem *> collisionList = collidingItems(); // The QList of items that the player is colliding with
    foreach(QGraphicsItem* h, collisionList)
    {
        if(dynamic_cast<Laser*>(h)) // If the colliding item is a laser
        {
            // Take away 20 health, remove the item from the scene, and delete the dynamically-allocated item
            health -= 20;
            scene()->removeItem(h);
            delete h;

            // When the player's health reaches 0, remove the player from the scene and delete the player.
            if(health <= 0)
            {
                emit Destroyed();
                QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveLeft()));
                QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(AnimateLeft()));
                QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveRight()));
                QObject::disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(AnimateRight()));
                scene()->removeItem(this);
                delete this;
                return;
            }
            emit HealthChanged(health); // Tells the health manager to update the player's health message
            return;
        }
    }
}

void ET::StopMovement()
{
    // Stops all timers in the ET class
    collisionTimer->stop();
    testTimer->stop();
    shootingTimer->stop();
    movementTimer.stop();
}

// Sets the array of the slides for the player (after exiting the flying saucer)
void ET::setAnimation()
{
    leftAnimation[0] = ":/MetroidLeft/Animation/MetroidLeft/frame_00_delay-0.05s.gif";
    leftAnimation[1] = ":/MetroidLeft/Animation/MetroidLeft/frame_01_delay-0.05s.gif";
    leftAnimation[2] = ":/MetroidLeft/Animation/MetroidLeft/frame_02_delay-0.05s.gif";
    leftAnimation[3] = ":/MetroidLeft/Animation/MetroidLeft/frame_03_delay-0.1s.gif";
    leftAnimation[4] = ":/MetroidLeft/Animation/MetroidLeft/frame_04_delay-0.05s.gif";
    leftAnimation[5] = ":/MetroidLeft/Animation/MetroidLeft/frame_05_delay-0.05s.gif";
    leftAnimation[6] = ":/MetroidLeft/Animation/MetroidLeft/frame_06_delay-0.05s.gif";
    leftAnimation[7] = ":/MetroidLeft/Animation/MetroidLeft/frame_07_delay-0.1s.gif";
    leftAnimation[8] = ":/MetroidLeft/Animation/MetroidLeft/frame_08_delay-0.05s.gif";
    leftAnimation[9] = ":/MetroidLeft/Animation/MetroidLeft/frame_09_delay-0.05s.gif";
    leftAnimation[10] = ":/MetroidLeft/Animation/MetroidLeft/frame_10_delay-0.05s.gif";
    leftAnimation[11] = ":/MetroidLeft/Animation/MetroidLeft/frame_11_delay-0.1s.gif";
    leftAnimation[12] = ":/MetroidLeft/Animation/MetroidLeft/frame_12_delay-0.05s.gif";
    leftAnimation[13] = ":/MetroidLeft/Animation/MetroidLeft/frame_13_delay-0.05s.gif";
    leftAnimation[14] = ":/MetroidLeft/Animation/MetroidLeft/frame_14_delay-0.05s.gif";
    leftAnimation[15] = ":/MetroidLeft/Animation/MetroidLeft/frame_15_delay-0.1s.gif";
    leftAnimation[16] = ":/MetroidLeft/Animation/MetroidLeft/frame_16_delay-0.05s.gif";
    leftAnimation[17] = ":/MetroidLeft/Animation/MetroidLeft/frame_17_delay-0.05s.gif";
    leftAnimation[18] = ":/MetroidLeft/Animation/MetroidLeft/frame_18_delay-0.05s.gif";
    leftAnimation[19] = ":/MetroidLeft/Animation/MetroidLeft/frame_19_delay-0.1s.gif";

    rightAnimation[0] = ":/MetroidRight/Animation/MetroidRight/frame_00_delay-0.05s.gif";
    rightAnimation[1] = ":/MetroidRight/Animation/MetroidRight/frame_01_delay-0.05s.gif";
    rightAnimation[2] = ":/MetroidRight/Animation/MetroidRight/frame_02_delay-0.05s.gif";
    rightAnimation[3] = ":/MetroidRight/Animation/MetroidRight/frame_03_delay-0.1s.gif";
    rightAnimation[4] = ":/MetroidRight/Animation/MetroidRight/frame_04_delay-0.05s.gif";
    rightAnimation[5] = ":/MetroidRight/Animation/MetroidRight/frame_05_delay-0.05s.gif";
    rightAnimation[6] = ":/MetroidRight/Animation/MetroidRight/frame_06_delay-0.05s.gif";
    rightAnimation[7] = ":/MetroidRight/Animation/MetroidRight/frame_07_delay-0.1s.gif";
    rightAnimation[8] = ":/MetroidRight/Animation/MetroidRight/frame_08_delay-0.05s.gif";
    rightAnimation[9] = ":/MetroidRight/Animation/MetroidRight/frame_09_delay-0.05s.gif";
    rightAnimation[10] = ":/MetroidRight/Animation/MetroidRight/frame_10_delay-0.05s.gif";
    rightAnimation[11] = ":/MetroidRight/Animation/MetroidRight/frame_11_delay-0.1s.gif";
    rightAnimation[12] = ":/MetroidRight/Animation/MetroidRight/frame_12_delay-0.05s.gif";
    rightAnimation[13] = ":/MetroidRight/Animation/MetroidRight/frame_13_delay-0.05s.gif";
    rightAnimation[14] = ":/MetroidRight/Animation/MetroidRight/frame_14_delay-0.05s.gif";
    rightAnimation[15] = ":/MetroidRight/Animation/MetroidRight/frame_15_delay-0.1s.gif";
    rightAnimation[16] = ":/MetroidRight/Animation/MetroidRight/frame_16_delay-0.05s.gif";
    rightAnimation[17] = ":/MetroidRight/Animation/MetroidRight/frame_17_delay-0.05s.gif";
    rightAnimation[18] = ":/MetroidRight/Animation/MetroidRight/frame_18_delay-0.05s.gif";
    rightAnimation[19] = ":/MetroidRight/Animation/MetroidRight/frame_19_delay-0.1s.gif";
}

// Returns the player's health
int ET::GetHealth() const
{
    return health;
}
