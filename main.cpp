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
    QColor color(255,255,255);
    QFont font;
    font.setPointSize(50);
    exitMessage.setPlainText("Press Enter to Exit Ship");
    exitMessage.setVisible(false);
    exitMessage.setPos(200,100);
    exitMessage.setFont(font);
    exitMessage.setDefaultTextColor(color);
    scene->addItem(&exitMessage);

    FlyingSaucer* ship = new FlyingSaucer(&exitMessage);
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
