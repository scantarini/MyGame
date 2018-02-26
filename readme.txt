Update 1:
Idea of this game:
I have been learning about the Graphics libraries through
online books and video tutorials.


The player model is a flying saucer that shoots a beam
to teleport people onto the ship.
As of now, I have implemented movement for both the
FlyingSaucer and Beam classes.
Also as of now, the Flying Saucer and the beam are
just rectangles.

After this, I plan on adding music.
Then I plan on making the people respond to the location
of the flying saucer.

I will wait to sync my other files to this repo until
I know this idea is ok.

Update 2:
I have the human class made.
Each human has a variable walking/running speed.
I plan on having the player fire additional objects
that will target the slowest-walking person that is
not already targeted.
I plan on implementing this using a priority queue
and smart pointers.

Aside:
I have also been reading up on the threading chapter of
the provided Qt programming pdf.
If time permits, I will apply concepts from that chapter.

Update 3:
I have figured out out how to add graphics and music to my project
I am currently trying to figure out how to add some basic animations to the human objects (and adding several different human images)

Along the way, I have learned about the following Qt libraries:
QGraphicsItem
QGraphicsPixmapItem
QMediaPlayer
QGraphicsScene
QGraphicsView
QList


I had some trouble trying to distinguish the human pointers from the other pointers (such as the flying saucer, the beams, and the seekers)
I created a spawner class that is in charge of spawning humans.
Instead of trying to access all game objects, I just used the children of the spawner using the childItems QList.

I am trying to store all humans moving across the screen as a priority queue of shared pointers.
The order for the priority_queue will be based on the human's walking speed.
The objects that track the player movement are the seekers.