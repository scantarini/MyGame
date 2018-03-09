#include "giant.h"
#include "laser.h"
#include "et.h"
#include <QString>

QString giantAnimation[3] =
{
    ":/Giant/Animation/Giant/00.gif",
    ":/Giant/Animation/Giant/01.gif",
    ":/Giant/Animation/Giant/02.gif"
};


Giant::Giant()
{}

void Giant::SetET(ET *player)
{
    et = player;
}
void Giant::Initialize()
{
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

void Giant::DecrementHealth()
{
    health -= 1;

    if(health <= 0)
    {
        et->StopMovement();
        emit Destroyed();
        giantTimer->stop();
        animationTimer->stop();
        shootTimer->stop();
        scene()->removeItem(this);
        return;
    }
    else
        emit HealthChanged(health);

}

int Giant::GetHealth() const
{
    return health;
}

void Giant::Destruct()
{
}

Giant::~Giant()
{
    delete giantTimer;
    delete musicTimer;
    delete animationTimer;
    delete music;
    delete shootTimer;
}

void Giant::Enter()
{
    if(y() < 0)
        setY(y() + 3);
    else
    {
        QObject::disconnect(giantTimer, SIGNAL(timeout()), this, SLOT(Enter()));
        shootTimer = new QTimer;
        QObject::connect(shootTimer, SIGNAL(timeout()), this, SLOT(Shoot()));
        shootTimer->start(1000);
    }
}

void Giant::Shoot()
{
    static int i = 0;
    Laser* laser0;
    Laser* laser1;
    Laser* laser2;
    Laser* laser3;
    Laser* laser4;
    Laser* laser5;
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

void Giant::Animate()
{
    setPixmap(QPixmap(giantAnimation[animationPosition]));
    ++animationPosition;
    if(animationPosition == 3) animationPosition = 0;
}

void Giant::StartMusic()
{
    music->setVolume(music->volume() + 2);
    if(music->volume() >= 50)
    {
        musicTimer->stop();
        QObject::disconnect(musicTimer, SIGNAL(timeout()), this, SLOT(StartMusic()));
    }
}
