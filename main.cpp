#include <QApplication>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "flyingsaucer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create the scene and put it in a view
    QGraphicsScene* scene = new QGraphicsScene;

    QGraphicsView* view = new QGraphicsView;
    scene->setSceneRect(0,0,1280,720);
    view->setScene(scene);
    view->setFixedSize(1280,720);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    FlyingSaucer* ship = new FlyingSaucer;
    scene->addItem(ship);
    ship->setPos(580, 150);
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();




    view->show();
    return a.exec();
}