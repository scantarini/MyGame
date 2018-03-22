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

    // Creates the scene and view
    QGraphicsScene* scene = new QGraphicsScene;
    QGraphicsView* view = new QGraphicsView;

    // Sets scene to be the scene of the view, sets the size of the scene, and sets the background image
    scene->setParent(view);
    scene->setSceneRect(0,0,1280,720);
    view->setScene(scene);
    view->setFixedSize(1280,720);
    scene->setBackgroundBrush(QBrush(QImage(":/Models/Background.gif")));

    // Prevents horizontal and vertical scrolling of the view
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Creates the message that tells the player how to exit the flying saucer.
    // This message is invisible until the flying saucer makes it visible.

    QGraphicsTextItem exitMessage;
    QFont font;
    font.setPointSize(50);
    exitMessage.setPlainText("Press Shift to Exit Ship");
    exitMessage.setVisible(false);
    exitMessage.setPos(200,100);
    exitMessage.setFont(font);
    exitMessage.setDefaultTextColor(Qt::white);
    scene->addItem(&exitMessage);



    // Creates the flying saucer with an initial position and makes it the focused object (responds to key presses)
    FlyingSaucer* ship = new FlyingSaucer(&exitMessage);
    scene->addItem(ship);
    ship->setPos(580, 150);
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();

    // Creates the messages for the giant health and the player health.
    // These messages will be used by the healthManager class.
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



    // Creates the player and giant objects and sets them both to be invisible.
    // The flying saucer will make these objects visible at an appropriate time.
    ET* player = new ET;
    player->setVisible(false);
    ship->SetET(player);
    Giant* giant;
    giant = new Giant;
    ship->SetGiant(giant);

    // Creates the exit button and adds it to the scene (initially invisible)
    GameEnder endButton;
    scene->addItem(&endButton);

    // Creates the health manager
    HealthManager health(player, &playerHealth, giant, &giantHealth, &endButton);

    // When the ET is made visible, set up the health displays for both the ET and the giant.
    QObject::connect(ship, SIGNAL(ETVisible()), &health, SLOT(DisplaySetup()));

    // When the health of the ET or the giant changes, update the display of the health messages.
    QObject::connect(player, SIGNAL(HealthChanged(int)), &health, SLOT(updatePlayerDisplay(int)));
    QObject::connect(giant, SIGNAL(HealthChanged(int)), &health, SLOT(updateGiantDisplay(int)));

    // When either the ET or giant health reach 0, end the game.
    QObject::connect(player, SIGNAL(Destroyed()), &health, SLOT(GameOver()));
    QObject::connect(giant, SIGNAL(Destroyed()), &health, SLOT(GameOver()));

    // When the game ends, display the exit button.
    QObject::connect(&health, SIGNAL(EndSignal()), &endButton, SLOT(display()));

    // When the visible exit button is pushed, exit the game
    QObject::connect(&endButton, SIGNAL(clicked()), &a, SLOT(quit()));


    view->show();

    return a.exec();
}
