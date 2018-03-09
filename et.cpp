#include "et.h"
#include "missile.h"
#include <QGraphicsScene>
#include "laser.h"

ET::ET()
{
    setAnimation();
    setPixmap(QPixmap(":/Models/standing4.png"));

    health = 100;
    walkDirection = 0;
    standingStill = true;
    lookingUp = false;

    fire.setMedia(QUrl("qrc:/Music/cannon.wav"));

    collisionTimer = new QTimer;
    shootingTimer = new QTimer;
    testTimer = new QTimer;

    shootingTimer->setSingleShot(true);
    testTimer->setSingleShot(true);

    QObject::connect(collisionTimer, SIGNAL(timeout()), this, SLOT(CheckCollision()));
    QObject::connect(testTimer, SIGNAL(timeout()), this, SLOT(StandStill()));
    collisionTimer->start(100);
    movementTimer.start(20);

}

ET::~ET()
{
    delete collisionTimer;
    delete testTimer;
    delete shootingTimer;
}

void ET::setMotherShip(FlyingSaucer *ship)
{
    motherShip = ship;
}

void ET::keyPressEvent(QKeyEvent *input)
{
    if(!lookingUp && input->key() == Qt::Key_A)
    {
        walkDirection = 0;
        QObject::connect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveLeft()));
        QObject::connect(&movementTimer, SIGNAL(timeout()), this, SLOT(AnimateLeft()));

    }
    else if(!lookingUp && input->key() == Qt::Key_D)
    {
        walkDirection = 1;
        QObject::connect(&movementTimer, SIGNAL(timeout()), this, SLOT(MoveRight()));
        QObject::connect(&movementTimer, SIGNAL(timeout()), this, SLOT(AnimateRight()));
    }
    else if(input->key()==Qt::Key_W)
    {
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
        if(fire.state() == QMediaPlayer::PlayingState)
            fire.setPosition(0);
        else
            fire.play();

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
        shootingTimer->start(100);
    }
    standingStill = false;
    testTimer->start(200);

}

void ET::keyReleaseEvent(QKeyEvent *released)
{
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
    if(!testTimer->isActive())
        testTimer->start(200);
}

void ET::AnimateLeft()
{
    static int i = 0;
    setPixmap(QPixmap(leftAnimation[i]));
    ++i;
    if(i==20) i = 0;
}

void ET::AnimateRight()
{
    static int i = 0;
    setPixmap(QPixmap(rightAnimation[i]));
    ++i;
    if(i == 20) i = 0;
}

void ET::MoveLeft()
{
    if(x()>10)
        setPos(x()-15, y());
}

void ET::MoveRight()
{
    if(x()<1090)
        setPos(x()+15, y());
}

void ET::MoveUp()
{
}

void ET::MoveDown()
{}

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

void ET::CheckCollision()
{
    QList<QGraphicsItem *> collisionList = collidingItems();
    foreach(QGraphicsItem* h, collisionList)
    {
        if(dynamic_cast<Laser*>(h))
        {
            health -= 20;
            scene()->removeItem(h);
            delete h;
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
            emit HealthChanged(health);
            return;
        }
    }
}

void ET::StopMovement()
{
    collisionTimer->stop();
    testTimer->stop();
    shootingTimer->stop();
    movementTimer.stop();
}


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

int ET::GetHealth() const
{
    return health;
}
