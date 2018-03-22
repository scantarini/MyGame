#include "flyingsaucer.h"
#include "beam.h"
#include "seeker.h"
#include "human.h"
#include "et.h"
#include "giant.h"

// Constructor
FlyingSaucer::FlyingSaucer(QGraphicsTextItem* exit)
{
    // Sets the starting image, the starting music, and sets the Z-priority value of the flying saucer to 2
    setZValue(2);
    setPixmap(QPixmap(":/UFO/Animation/Frames/00.gif"));
    fire.setMedia(QUrl("qrc:/Music/Galaga.mp3"));

    // Starts the timers
    time.start(30); // Timer for the movement of the flying saucer
    spawnTimer.start(500);
    animationTimer.start(50);

    QObject::connect(&spawnTimer, SIGNAL(timeout()), this, SLOT(MakeHuman()));
    QObject::connect(&animationTimer, SIGNAL(timeout()), this, SLOT(Animate()));

    // Initializes the flying saucer images
    initializeAnimation();
    seekerCounter = 0;          // The number of seekers on the screen
    exitable = false;           // Whether or not the player can exit the flying saucer
    leaving = false;            // If the player has exited the flying saucer
    exitMessage = exit;         // Tells the player to press shift to exit the flying saucer
    music = new QMediaPlayer;   // Media player for the backround music
    music->setMedia(QUrl("qrc:/Music/Metroid NES Music - Ridleys Hideout.mp3")); // Sets the background music
    music->play();              // Plays the background music
}

// Returns the start of the vector of humans that is sorted by walking speed (increasing)
Human *FlyingSaucer::targetSlowestHuman()
{
    if(population.empty()) return nullptr;
    return population[0];
}

// Controls the flying saucer's movement
void FlyingSaucer::keyPressEvent(QKeyEvent *input)
{
    /***************************************************
    * W - move up
    * A - move left
    * S - move down
    * D - move right
    * Space - fire a beam
    * X - Fire a seeker
    * Shift - Exit the flying saucer (if exitable)
    ***************************************************/
    if(input->key() == Qt::Key_W)
        QObject::connect(&time, SIGNAL(timeout()), this, SLOT(MoveUp()));
    else if(input->key() == Qt::Key_S)
        QObject::connect(&time, SIGNAL(timeout()), this, SLOT(MoveDown()));
    else if(input->key() == Qt::Key_A)
        QObject::connect(&time, SIGNAL(timeout()), this, SLOT(MoveLeft()));
    else if(input->key() == Qt::Key_D)
        QObject::connect(&time, SIGNAL(timeout()), this, SLOT(MoveRight()));

    else if(input->key() == Qt::Key_Space)
    {
        if(fire.state() == QMediaPlayer::PlayingState)
            fire.setPosition(0);
        else
            fire.play();

        Beam* greenBeam = new Beam; // Not green. It is a ball.
        greenBeam->SetShip(this);

        // Sets the starting location of the beam (it alternates between 3 positions)
        if(seekerCounter%3==0)
            greenBeam->setPos(x()+80,y()+55);
        else if(seekerCounter%3==1)
            greenBeam->setPos(x()+140,y()+55);
        else if(seekerCounter%3==2)
            greenBeam->setPos(x()+18,y()+55);
        scene()->addItem(greenBeam);
        seekerCounter++;

    }
    else if(input->key() == Qt::Key_X)
    {
        // If the shooting sound is playing, play it again from the start
        if(fire.state() == QMediaPlayer::PlayingState)
            fire.setPosition(0);
        else
            fire.play();

        // Creates a seeker and adds it to the scene
        Seeker* seeker = new Seeker;
        seeker->SetShip(this);
        if(seekerCounter%3==0)
            seeker->setPos(x()+80,y()+55);
        else if(seekerCounter%3==1)
            seeker->setPos(x()+140,y()+55);
        else if(seekerCounter%3==2)
            seeker->setPos(x()+18,y()+55);
        scene()->addItem(seeker);
        seekerCounter++;
    }
    else if(exitable && input->key() == Qt::Key_Shift)
    {
        // When the player exits the ship,
        /*
        * Set the ET to visible
        * Emit to the health manager that the ET is visible
        * Add the ET to the scene
        * Set the ET to respond to key presses (focused item)
        * Tells the flying saucer to exit the screen
        */
        et->setVisible(true);
        emit ETVisible();
        exitMessage->setPlainText("");
        et->setMotherShip(this);
        et->setPos(x(),500);
        scene()->addItem(et);
        et->setFlag(QGraphicsItem::ItemIsFocusable);
        et->setFocus();
        spawnTimer.stop();
        leaving = true;
        QObject::connect(&time, SIGNAL(timeout()), this, SLOT(Leave()));
        QObject::disconnect(&time, SIGNAL(timeout()), this, SLOT(MoveDown()));
    }


    // Sets the screen boundaries for the flying saucer
    if(x() < 10)
        setPos(10,y());
    if(y() > 400)
        setPos(x(),400);
    if(x() > 1170)
        setPos(1170,y());
    if(y() < 5)
        setPos(x(),5);

}

// Controls actions associated with key releases
void FlyingSaucer::keyReleaseEvent(QKeyEvent *released)
{
    if(released->key() == Qt::Key_W)
        QObject::disconnect(&time, SIGNAL(timeout()), this, SLOT(MoveUp()));
    else if(released->key() == Qt::Key_S)
        QObject::disconnect(&time, SIGNAL(timeout()), this, SLOT(MoveDown()));
    else if(released->key() == Qt::Key_A)
        QObject::disconnect(&time, SIGNAL(timeout()), this, SLOT(MoveLeft()));
    else if(released->key() == Qt::Key_D)
        QObject::disconnect(&time, SIGNAL(timeout()), this, SLOT(MoveRight()));
}

// Imposes an order on Humans for the population vector
bool FlyingSaucer::isLess(Human* &h1, Human* &h2)
{
    if(h1 == nullptr) return true;
    if(h2 == nullptr) return false;
    if(h1->GetSpeed() < h2->GetSpeed()) return true;
    return false;
}

// Inserts a human into the population vector
void FlyingSaucer::populationInsert(Human* h1)
{
    // do the maintain before this
    if(h1==nullptr) return;
    if(population.empty())
    {
        population.push_back(h1);
        return;
    }

    if(!isLess(h1,*(population.end() - 1)))
    {
        population.insert(population.end(), h1);
        return;
    }
    for(std::vector<Human*>::iterator i =  population.begin(); i != population.end(); i++)
    {
        if(isLess(h1,(*i)))
        {
            population.insert(i, h1);
            return;
        }
    }


}

// Removes all humans that have been caught from the scene and deallocates their memory
void FlyingSaucer::populationMaintenance()
{
    for(std::vector<Human*>::iterator i = population.begin(); i != population.end(); i++)
    {
        if((*i) == nullptr) // If the human's pointer has been set to null, remove i from the vector
        {
            population.erase(i);
            i--;
            continue;
        }
        if((*i)->isCaught()) // if a human has been caught, remove them from the scene, delete their memory, and remove them from the vector
        {
            scene()->removeItem((*i));
            delete (*i);
            (*i) == nullptr;
            population.erase(i);
            i--;
        }
    }
}

// Destructor
FlyingSaucer::~FlyingSaucer()
{}

// Sets the ET to leave the scene
void FlyingSaucer::SetET(ET *player)
{
    et = player;
}

// Returns true if the flying saucer is leaving the screen (if the player has exited)
bool FlyingSaucer::IsLeaving() const
{
    return leaving;
}

// Sets the pointer to the giant (UFO)
void FlyingSaucer::SetGiant(Giant *g)
{
    giant = g;
}

// Spawns a human and inserts them into the population vector
void FlyingSaucer::MakeHuman()
{
    if(population.size() < 8)
    {
        Human* human = new Human();
        human->SetMotherShip(this);
        scene()->addItem(human);
        populationInsert(human);
    }
}

// Updates the UFO image (by running through the animationSlides array)
void FlyingSaucer::Animate()
{
    static int i = 0;
    setPixmap(QPixmap(animationSlides[i]));
    i++;
    if(i==24) i = 0;
}

// Moves the flying saucer up (also sets screen boundaries)
void FlyingSaucer::MoveUp()
{
    if(y()>5)
    setPos(x(), y()-7);
    if(exitable && y() < 390)
    {
        exitable = false;
        exitMessage->setVisible(false);
    }
}

// Moves the flying saucer down (also sets screen boundaries)
void FlyingSaucer::MoveDown()
{
    if(y() < 400)
    setPos(x(), y()+7);
    if(!exitable && y() > 390)
    {
        exitable = true;
        exitMessage->setVisible(true);
    }
}

// Moves the flying saucer left (also sets screen boundaries)
void FlyingSaucer::MoveLeft()
{
    if(x()>10)
        setPos(x()-7, y());
}

// Moves the flying saucer right (also sets screen boundaries)
void FlyingSaucer::MoveRight()
{
    if(x()<1090)
        setPos(x()+7, y());
}

// Sets the flying saucer to a leaving state
void FlyingSaucer::Leave()
{
    setY(y()-4); // moves the player up (even past the top of the screen)
    music->setVolume(music->volume()-1); // fades out the background music
    if(y() < -200 && population.empty())
    {
        giant->setVisible(true);   // When all the Human's have disappeared, set the giant (UFO) as visible
        giant->Initialize();       // Initializes attributes of the giant
        giant->SetET(et);          // Provides the giant with a pointer to the ET (player after exiting the screen)

        // Adds the giant to the scene and removes the flying saucer
        scene()->addItem(giant);
        scene()->removeItem(this);
        QObject::disconnect(&time, SIGNAL(timeout()), this, SLOT(Leave()));
        time.stop();
        animationTimer.stop();
        delete music;
        delete this;
    }

}

// The animation images for the flying saucer
void FlyingSaucer::initializeAnimation()
{
    animationSlides[0] = ":/UFO/Animation/Frames/00.gif";
    animationSlides[1] = ":/UFO/Animation/Frames/01.gif";
    animationSlides[2] = ":/UFO/Animation/Frames/02.gif";
    animationSlides[3] = ":/UFO/Animation/Frames/03.gif";
    animationSlides[4] = ":/UFO/Animation/Frames/04.gif";
    animationSlides[5] = ":/UFO/Animation/Frames/05.gif";
    animationSlides[6] = ":/UFO/Animation/Frames/06.gif";
    animationSlides[7] = ":/UFO/Animation/Frames/07.gif";
    animationSlides[8] = ":/UFO/Animation/Frames/08.gif";
    animationSlides[9] = ":/UFO/Animation/Frames/09.gif";
    animationSlides[10] = ":/UFO/Animation/Frames/10.gif";
    animationSlides[11] = ":/UFO/Animation/Frames/11.gif";
    animationSlides[12] = ":/UFO/Animation/Frames/12.gif";
    animationSlides[13] = ":/UFO/Animation/Frames/13.gif";
    animationSlides[14] = ":/UFO/Animation/Frames/14.gif";
    animationSlides[15] = ":/UFO/Animation/Frames/15.gif";
    animationSlides[16] = ":/UFO/Animation/Frames/16.gif";
    animationSlides[17] = ":/UFO/Animation/Frames/17.gif";
    animationSlides[18] = ":/UFO/Animation/Frames/18.gif";
    animationSlides[19] = ":/UFO/Animation/Frames/19.gif";
    animationSlides[20] = ":/UFO/Animation/Frames/20.gif";
    animationSlides[21] = ":/UFO/Animation/Frames/21.gif";
    animationSlides[22] = ":/UFO/Animation/Frames/22.gif";
    animationSlides[23] = ":/UFO/Animation/Frames/23.gif";


}
