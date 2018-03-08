NOTE: There is music. Be careful for the volume.

Controls:
While in the flying saucer:
w - moves the flying saucer up
a - moves the flying saucer left
s - moves the flying saucer down
d - moves the flying saucer right
space - fires a beam that continues straight down
x - fires a projectile (seeker) that targets the slowest human on the field
shift - allows the player to exit the flying saucer (when sufficiently close to the ground)

While not in flying saucer:
a - moves the player left
d - moves the player right
w - makes the player look upwards
space - shoots in the direction the player is facing



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
-How to reset the focused object to allow the keyinput to act
 on different objects.


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
QGraphicsTextItem
QFont
QColor

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

2. I had a lot of trouble trying to add a QGraphicsTextItem to
the scene. I believe this is because this particular type does
not allow copying or outside access, and so there is no access
allowed for the scene (which was declared in main)

3. I had difficulty making the running animation for the ET
player smooth. This is because keypresses are not continuous.
When holding a key, the key is just pushed somewhat rapidly.
This caused the standing animation to flick in and out of the
running animation. This is what lead me to learn about
single-shot QTimers. I used a single-shot QTimer to fix
this problem.

4. I had some trouble with the ET class in the sense that the
class is not allowed to have more than one QTimer object.
To fix this, I changed one of the QTimers to a QTimer*.

Plans:
1. Add health displays for player and enemy classes.
using smart pointers.
2. I plan on learning how to add live messages to views.
to output some information about the current state of the game.
3. I plan on learning to switch the view between different scene objects.
to create a loading/pause screen.
4. Learning about the QMovie library.
