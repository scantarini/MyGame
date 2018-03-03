#include "beam.h"
#include "flyingsaucer.h"
#include "spawner.h"
#include "human.h"




FlyingSaucer::FlyingSaucer()
{
    setRect(0,0,150,50);
}

void FlyingSaucer::keyPressEvent(QKeyEvent *input)
{
    if(input->key() == Qt::Key_W)
        setPos(x(), y()-15);
    else if(input->key() == Qt::Key_S)
        setPos(x(), y()+15);
    else if(input->key() == Qt::Key_A)
        setPos(x()-15, y());
    else if(input->key() == Qt::Key_D)
        setPos(x()+15, y());
    else if(input->key() == Qt::Key_Q)
        setPos(x()-10, y()-10);
    else if(input->key() == Qt::Key_E)
        setPos(x()+10, y()-10);
    else if(input->key() == Qt::Key_Z)
        setPos(x()-10, y()+10);
    else if(input->key() == Qt::Key_C)
        setPos(x()+10, y()+10);
    else if(input->key() == Qt::Key_Left)
        setPos(x()-550, y());
    else if(input->key() == Qt::Key_Right)
        setPos(x()+550, y());

    else if(input->key() == Qt::Key_Space)
    {
        Beam* greenBeam = new Beam;
        greenBeam->SetShip(this);
        greenBeam->setRect(x(),y(),10,30);
        scene()->addItem(greenBeam);
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

void FlyingSaucer::SetSpawner(Spawner *s)
{
    spawner = s;
}

Spawner *FlyingSaucer::GetSpawner() const
{
    return spawner;
}
