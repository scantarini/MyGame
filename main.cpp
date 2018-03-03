#include <QApplication>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QPixmap>
#include <QImage>
#include <QBrush>
#include "flyingsaucer.h"
#include "spawner.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create the scene and put it in a view
    QGraphicsScene* scene = new QGraphicsScene;

    QGraphicsView* view = new QGraphicsView;
    scene->setSceneRect(0,0,1280,720);
    view->setScene(scene);
    view->setFixedSize(1280,720);
    scene->setBackgroundBrush(QBrush(QImage(":/Models/Background.gif")));


    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    FlyingSaucer* ship = new FlyingSaucer;
    scene->addItem(ship);
    ship->setPos(580, 150);
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();

    Spawner* spawner = new Spawner;
    scene->addItem(spawner);
    ship->SetSpawner(spawner);

    QMediaPlayer* music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/Music/Metroid NES Music - Ridleys Hideout.mp3"));
    music->play();




    view->show();
    return a.exec();
}
