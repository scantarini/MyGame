#include <QApplication>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "flyingsaucer.h"
#include "spawner.h"
#include <QMediaPlayer>
#include <QPixmap>
#include <QImage>
#include <QBrush>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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


    QMediaPlayer* music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/Music/Metroid NES Music - Ridleys Hideout.mp3"));
    music->play();

    view->show();

    return a.exec();
}
