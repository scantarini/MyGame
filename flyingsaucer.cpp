#include "flyingsaucer.h"
#include "beam.h"
#include "seeker.h"
#include "human.h"

QString exitText = "Press Enter to Exit Ship";
FlyingSaucer::FlyingSaucer(QGraphicsTextItem* exit)
{
    setPixmap(QPixmap(":/UFO/Animation/Frames/00.gif"));
    fire.setMedia(QUrl("qrc:/Music/Galaga.mp3"));

    time.start(30);
    spawnTimer.start(500);
    animationTimer.start(50);

    QObject::connect(&spawnTimer, SIGNAL(timeout()), this, SLOT(MakeHuman()));
    QObject::connect(&animationTimer, SIGNAL(timeout()), this, SLOT(Animate()));

    initializeAnimation();
    seekerCounter = 0;
    exitable = false;
    exitMessage = exit;
}

Human *FlyingSaucer::targetSlowestHuman()
{
    if(population.empty()) return nullptr;
    return population[0];
}

void FlyingSaucer::keyPressEvent(QKeyEvent *input)
{
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

        Beam* greenBeam = new Beam;
        greenBeam->SetShip(this);

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
        if(fire.state() == QMediaPlayer::PlayingState)
            fire.setPosition(0);
        else
            fire.play();

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


    if(x() < 10)
        setPos(10,y());
    if(y() > 400)
        setPos(x(),400);
    if(x() > 1170)
        setPos(1170,y());
    if(y() < 5)
        setPos(x(),5);

}

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

bool FlyingSaucer::isLess(Human* &h1, Human* &h2)
{
    if(h1 == nullptr) return true;
    if(h2 == nullptr) return false;
    if(h1->GetSpeed() < h2->GetSpeed()) return true;
    return false;
}

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

void FlyingSaucer::populationMaintenance()
{
    for(std::vector<Human*>::iterator i = population.begin(); i != population.end(); i++)
    {
        if((*i) == nullptr)
        {
            population.erase(i);
            i--;
            continue;
        }
        if((*i)->isCaught())
        {
            scene()->removeItem((*i));
            delete (*i);
            (*i) == nullptr;
            population.erase(i);
            i--;
        }
    }
}

FlyingSaucer::~FlyingSaucer()
{}

void FlyingSaucer::MakeHuman()
{
    if(population.size() < 8)
    {
        Human* human = new Human();
        human->SetMotherShip(this);
        scene()->addItem(human);
        populationInsert(human);
        //if(population.size()==10) exit(0);
    }
}

void FlyingSaucer::Animate()
{
    static int i = 0;
    setPixmap(QPixmap(animationSlides[i]));
    i++;
    if(i==24) i = 0;
}

void FlyingSaucer::MoveUp()
{
    if(y()>5)
    setPos(x(), y()-7);
    if(messageDisplayed && y() < 390)
    {
        messageDisplayed = false;
        exitMessage->setVisible(false);
    }
}

void FlyingSaucer::MoveDown()
{
    if(y() < 400)
    setPos(x(), y()+7);
    if(!messageDisplayed && y() > 390)
    {
        messageDisplayed = true;
        exitMessage->setVisible(true);
    }
}

void FlyingSaucer::MoveLeft()
{
    if(x()>10)
        setPos(x()-7, y());
}

void FlyingSaucer::MoveRight()
{
    if(x()<1090)
        setPos(x()+7, y());
}

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
