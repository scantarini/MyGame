#include "giant.h"
#include "laser.h"
#include "et.h"
#include <QString>

// The animation images for the giant
QString giantAnimation[3] =
{
    ":/Giant/Animation/Giant/00.gif",
    ":/Giant/Animation/Giant/01.gif",
    ":/Giant/Animation/Giant/02.gif"
};

// Constructor
Giant::Giant()
{}

// Sets the pointer to the ET (the player after exiting the flying saucer)
void Giant::SetET(ET *player)
{
    et = player;
}

// Initializes attributes for the giant.
// This takes place after the constructor so the giant can be modified by other classes before it influences the scene
// (such as by changing the music)
void Giant::Initialize()
{
    /*
    * Initializes health to 100
    * Initializes isEntered to false (tells that the entering action for the giant has not completed, so don't start shooting lasers)
    * Sets the image of the giant to the first position in the giantAnimation array
    * Begins the entering process of the giant
    * Plays the new music (and fades it in with the StartMusic() function)
    */
    health = 100;
    isEntered = false;
    animationPosition = 0;
    setPos(0,-250);
    setPixmap(QPixmap(":/Giant/Animation/Giant/00.gif"));
    giantTimer = new QTimer;
    QObject::connect(giantTimer, SIGNAL(timeout()), this, SLOT(Enter()));
    giantTimer->start(30);

    animationTimer = new QTimer;
    QObject::connect(animationTimer, SIGNAL(timeout()), this, SLOT(Animate()));
    animationTimer->start(150);
    music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/Music/Benny Hill 8 bit.mp3"));
    music->play();
    music->setVolume(1);

    musicTimer = new QTimer;
    QObject::connect(musicTimer, SIGNAL(timeout()), this, SLOT(StartMusic()));
    musicTimer->start(75);
}

// Decreases the giant's health by 1 (when it is hit by a missile)
void Giant::DecrementHealth()
{
    health -= 1;

    // If the giant is destroyed, stop it from shooting and stop its animation
    if(health <= 0)
    {
        et->StopMovement();
        emit Destroyed();
        giantTimer->stop();
        animationTimer->stop();
        shootTimer->stop();
        return;
    }
    else
        emit HealthChanged(health); // Tells the health manager that the health of the giant has changed

}

// Returns the giant's health
int Giant::GetHealth() const
{
    return health;
}

// Deletes all dynamically-allocated memory
Giant::~Giant()
{
    delete giantTimer;
    delete musicTimer;
    delete animationTimer;
    delete music;
    delete shootTimer;
}

// Controls the entering movement for the giant
void Giant::Enter()
{
    if(y() < 0)
        setY(y() + 3);
    else
    {
        QObject::disconnect(giantTimer, SIGNAL(timeout()), this, SLOT(Enter()));
        shootTimer = new QTimer;

        // Gets the giant to start shooting
        QObject::connect(shootTimer, SIGNAL(timeout()), this, SLOT(Shoot()));
        shootTimer->start(1000);
    }
}

// Adds lasers to the scene
void Giant::Shoot()
{
    // Creates 5 new lasers
    static int i = 0;
    Laser* laser0;
    Laser* laser1;
    Laser* laser2;
    Laser* laser3;
    Laser* laser4;
    Laser* laser5;

    // Fires the lasers in different (preset) patterns
    if(i%3==0)
    {
        laser0 = new Laser(15,150,7,5);
        laser1 = new Laser(140,120,5,5);
        laser2 = new Laser(250,190,4,5);
        laser3 = new Laser(670,100,0,6);
        laser4 = new Laser(1090,190,-6,5);
        laser5 = new Laser(1200,100,-7,5);
    }
    else if(i%3==1)
    {
        laser0 = new Laser(15,150,3,5);
        laser1 = new Laser(140,120,3,5);
        laser2 = new Laser(250,190,2,5);
        laser3 = new Laser(670,100,0,6);
        laser4 = new Laser(1090,190,-3,5);
        laser5 = new Laser(1200,100,-5,5);
    }
    else
    {
        laser0 = new Laser(15,150,0,5);
        laser1 = new Laser(140,120,0,5);
        laser2 = new Laser(250,190,0,5);
        laser3 = new Laser(670,100,0,6);
        laser4 = new Laser(1090,190,-0,5);
        laser5 = new Laser(1200,100,-0,5);
    }
    scene()->addItem(laser0);
    scene()->addItem(laser1);
    scene()->addItem(laser2);
    scene()->addItem(laser3);
    scene()->addItem(laser4);
    scene()->addItem(laser5);
    ++i;
}

// Updates the animation image in the giantAnimation array
void Giant::Animate()
{
    setPixmap(QPixmap(giantAnimation[animationPosition]));
    ++animationPosition;
    if(animationPosition == 3) animationPosition = 0;
}

// Fades in the new background music
void Giant::StartMusic()
{
    music->setVolume(music->volume() + 2);
    if(music->volume() >= 50)
    {
        musicTimer->stop();
        QObject::disconnect(musicTimer, SIGNAL(timeout()), this, SLOT(StartMusic()));
    }
}
