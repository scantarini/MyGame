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
#include "healthmanager.h"
#include "gameender.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene* scene = new QGraphicsScene;

    QGraphicsView* view = new QGraphicsView;
    scene->setParent(view);
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

    QGraphicsTextItem playerHealth;
    QGraphicsTextItem giantHealth;
    font.setPointSize(30);
    playerHealth.setFont(font);
    giantHealth.setFont(font);
    playerHealth.setPos(400,0);
    giantHealth.setPos(0,0);
    scene->addItem(&playerHealth);
    scene->addItem(&giantHealth);
    playerHealth.setZValue(3);
    giantHealth.setZValue(3);

    playerHealth.setDefaultTextColor(Qt::blue);
    giantHealth.setDefaultTextColor(Qt::black);




    ET* player = new ET;
    player->setVisible(false);
    ship->SetET(player);
    Giant* giant;
    giant = new Giant;
    ship->SetGiant(giant);

    GameEnder endButton;
    scene->addItem(&endButton);
    HealthManager health(player, &playerHealth, giant, &giantHealth, &endButton);
    QObject::connect(ship, SIGNAL(ETVisible()), &health, SLOT(DisplaySetup()));
    QObject::connect(player, SIGNAL(HealthChanged(int)), &health, SLOT(updatePlayerDisplay(int)));
    QObject::connect(giant, SIGNAL(HealthChanged(int)), &health, SLOT(updateGiantDisplay(int)));
    QObject::connect(player, SIGNAL(Destroyed()), &health, SLOT(GameOver()));
    QObject::connect(giant, SIGNAL(Destroyed()), &health, SLOT(GameOver()));
    QObject::connect(&health, SIGNAL(EndSignal()), &endButton, SLOT(display()));
    QObject::connect(&endButton, SIGNAL(clicked()), &a, SLOT(quit()));
    view->show();

    return a.exec();
}
