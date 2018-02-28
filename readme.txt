Update 1:
Idea of this game:
The player model is a flying saucer that shoots a beam
to teleport people onto the ship.

Features:
- Move an animated flying saucer
- Fire two types of projectiles from the flying saucer:
    - A beam that travels straight down
    - A seeker that targets the slowest human object
- Animated human characters with variable speeds
- A background image for the players to run along
- Sound effects (music and projectile noises)

Through this project, I have learned/implemented the following:
-How to make a Qt widget class
-How to manage scenes and views inside a Qt program
-How to connect QTimers to public slots in my widget classes
-How to implement images and audio files into my Qt programs
-How to make a Qt program respond to keystrokes
-How to update an image on a timer to create animation.

Along the way, I have learned about the following Qt libraries:
QTimer
QGraphicsRect
QGraphicsRectItem
QGraphicsItem
QGraphicsPixmapItem
QMediaPlayer
QGraphicsScene
QGraphicsView
QList

Difficulties:
1.  I had trouble maintaining a sorted data structure that
keeps track of all human objects.
My goal was for the flying saucer to have information on
all human objects.
I originally had a spawner class that handled all memory
allocation for Human objects.
Rather than passing this information from the Spawner class
to the flying saucer, I set the flying saucer to manage the
memory allocation for all human objects.
And now I maintain a sorted vector of Human objects within
the FlyingSaucer class.
The order is by walking speed.

Plans:
1. Allow players to enter and leave from doors on the background image.
Keep track of how many Humans are currently inside the building
using smart pointers.
2. I plan on learning how to add live messages to a views
to output some information about the current state of the game.
3. I plan on learning to switch the view between scene objects
to create a loading/pause screen.
4. Learning about the QMovie library