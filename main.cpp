#include <QApplication>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "flyingsaucer.h"
#include <QMediaPlayer>
#include <QPixmap>
#include <QImage>
#include <QBrush>
#include <QGraphicsTextItem>
#include "et.h"
#include "giant.h"

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


    QGraphicsTextItem exitMessage;
    QFont font;
    font.setPointSize(50);
    exitMessage.setPlainText("Press Shift to Exit Ship");
    exitMessage.setVisible(false);
    exitMessage.setPos(200,100);
    exitMessage.setFont(font);
    exitMessage.setDefaultTextColor(Qt::white);
    scene->addItem(&exitMessage);

    FlyingSaucer* ship = new FlyingSaucer(&exitMessage);
    scene->addItem(ship);
    ship->setPos(580, 150);
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();

    ET* player = new ET;
    ship->SetET(player);

    view->show();

    return a.exec();
}
