# LynxBoilerplate

A boilerplate for building Atari Lynx games on top of. Based on the Pong template orginally posted by Karri on Mon Nov 26, 2012

Code descript

Include some libraries:
```
#include <lynx.h>
#include <tgi.h>
#include <6502.h>
#include <joystick.h>
#include <stdlib.h>
```
Create a literal sprite for a paddle:
```
unsigned char paddle[] = {
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  0
};
```
Create a literal sprite for the ball:
```
unsigned char ball[] = {
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  0
};
```
Create a literal sprite of a wall element that we can stretch later:
```
unsigned char wall[] = {
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  0
};
```
Then we create a widget object to hold out paddle or ball. To this widget object we add two extra fields: horizontal velocity and vertical velocity. This allows the sprite to have a property of speed.
```
typedef struct {
  char collindex;
  SCB_REHV sprite;
  PENPAL_1;
  signed char hvel;
  signed char vvel;
} sprite_t;
```
Then we need to define the sprite stucture for our paddles:
```
sprite_t LeftPaddle = {
  0,
  {
    BPP_1 | TYPE_NORMAL,
    LITERAL | REHV,
    1,
    0,
    paddle,
    10, 73, 256, 256
  },
  {COLOR_GREY},
  0, 0
};

sprite_t RightPaddle = {
  0,
  {
    BPP_1 | TYPE_NORMAL,
    LITERAL | REHV,
    2,
    0,
    paddle,
    159-10-6, 70, 256, 256
  },
  {COLOR_GREY},
  0, 0
};
```
We also need to have walls from which the ball can bounce:
```
sprite_t TopWall = {
  0,
  {
    BPP_1 | TYPE_NORMAL,
    LITERAL | REHV,
    3,
    0,
    wall,
    -24, 1, 160 / 6 * 256, 256
  },
  {COLOR_GREEN},
  0, 0
};

sprite_t BottomWall = {
  0,
  {
    BPP_1 | TYPE_NORMAL,
    LITERAL | REHV,
    4,
    0,
    wall,
    -24, 101-4, 160 / 6 * 256, 256
  },
  {COLOR_GREEN},
  0, 0
};
Last but not least we need a ball:

sprite_t Ball = {
  0,
  {
    BPP_1 | TYPE_NORMAL,
    LITERAL | REHV,
    5,
    0,
    ball,
    10, 10, 256, 256
  },
  {COLOR_GREY},
  2, 1
};
```
Please note that now all our widgets have id's also. I gave a collision index to every element while I created them.
```
LeftPaddle = 1
RightPaddle = 2
TopWall = 3
BottomWall = 4
Ball = 5
```
We need these later on to know who collided with what.

Then we set up some score counters:
```
signed RightScore = 0;
signed LeftScore = 0;
```
Now it is time to start writing the program itself. We start with defining the main:
```
void main()
{
  unsigned char joy;
  char buffer[16];
```
Here I also defines a char for holding the joypad and a buffer for integer to ascii conversions later in the game.

The we need to initialize the chips:
```
joy_install(&lynxjoy);
tgi_install(&lynxtgi);
tgi_init();
tgi_setcollisiondetection(1);
CLI();
```
Now we get to the main loop that runs forever. (In the real pong we usually stop when either player reaches 15 points).
```
while (1) {
Then we erase the collision buffers and set the paddles grey.

while (tgi_busy())
	 ;
/* Erase collision buffer */
tgi_clear();
LeftPaddle.penpal[0] = COLOR_GREY;
RightPaddle.penpal[0] = COLOR_GREY;
Now we check if the players press any buttons (up/down or A/B):

/* Move paddles */
joy = joy_read(JOY_1);
if (JOY_BTN_UP(joy)) {
	 LeftPaddle.sprite.vpos -= 1;
}
if (JOY_BTN_DOWN(joy)) {
	 LeftPaddle.sprite.vpos += 1;
}
if (JOY_BTN_FIRE(joy)) {
	 RightPaddle.sprite.vpos -= 1;
}
if (JOY_BTN_FIRE2(joy)) {
	 RightPaddle.sprite.vpos += 1;
}
```
Then we let the ball move and add score if the ball exits the screen.
```
Ball.sprite.hpos += Ball.hvel;
if (Ball.sprite.hpos < 3) {
	 RightScore++;
	 Ball.sprite.hpos = RightPaddle.sprite.hpos;
	 Ball.sprite.vpos = RightPaddle.sprite.vpos + 10;
}
if (Ball.sprite.hpos > 160 -3) {
	 LeftScore++;
	 Ball.sprite.hpos = LeftPaddle.sprite.hpos;
	 Ball.sprite.vpos = LeftPaddle.sprite.vpos + 10;
}
Ball.sprite.vpos += Ball.vvel;
```
Then we paint out walls and paddles and last our ball to see if it collides.
```
/* Paint stationary sprites */
tgi_sprite(&TopWall.sprite);
tgi_sprite(&BottomWall.sprite);
tgi_sprite(&LeftPaddle.sprite);
tgi_sprite(&RightPaddle.sprite);

/* Draw last collidable sprite */
tgi_sprite(&Ball.sprite);
After the collision has occurred we can see who collided with what.

/* Examine collisions */
switch (Ball.collindex) {
case 0:
	 break;
case 1:
	 Ball.hvel = 2;
	 LeftPaddle.penpal[0] = COLOR_RED;
	 tgi_sprite(&LeftPaddle.sprite);
	 break;
case 2:
	 Ball.hvel = -2;
	 RightPaddle.penpal[0] = COLOR_RED;
	 tgi_sprite(&RightPaddle.sprite);
	 break;
case 3:
case 4:
	 Ball.vvel = -Ball.vvel;
	 break;
default:
	 break;
}
```
Then we print the score for this round and update the display.
```
tgi_setcolor(COLOR_WHITE);
itoa(LeftScore, &buffer[0], 10);
tgi_outtextxy(40, 10, buffer);
itoa(RightScore, &buffer[0], 10);
tgi_outtextxy(120, 10, buffer);
tgi_updatedisplay();
}
}
```
That's it. To compile it we can run the codes manually or use a Makefile.

Here is a Makefile
```
RM=rm -f
CO=co65
CC=cc65
AS=ca65
CL=cl65

ifeq ($(CC65_HOME),)
	 CC65_HOME=/usr/local/lib/cc65
endif
ifeq ($(CC65_INC),)
	 CC65_INC=$(CC65_HOME)/include
endif
ifeq ($(CC65_ASMINC),)
	 CC65_ASMINC=$(CC65_HOME)/asminc
endif

all:
	 $(CP) $(CC65_HOME)/tgi/lynx-160-102-16.tgi .
	 $(CP) $(CC65_HOME)/joy/lynx-stdjoy.joy .
	 $(CO) --code-label _lynxtgi lynx-160-102-16.tgi
	 $(CO) --code-label _lynxjoy lynx-stdjoy.joy
	 $(AS) -t lynx lynx-160-102-16.s
	 $(AS) -t lynx lynx-stdjoy.s
	 $(CC) -t lynx pong.c
	 $(AS) -t lynx pong.s
	 $(CL) -t lynx -o pong.lnx -m pong.map pong.o lynx-160-102-16.o lynx-stdjoy.o lynx.lib

clean:
	 $(RM) pong.lnx
	 $(RM) pong.s
	 $(RM) pong.o
	 $(RM) lynx-stdjoy.s
	 $(RM) lynx-stdjoy.o
	 $(RM) lynx-stdjoy.joy
	 $(RM) lynx-160-102-16.s
	 $(RM) lynx-160-102-16.o
	 $(RM) lynx-160-102-16.tgi
   ```
To use the Makefile you simply type "make".

ref: http://atariage.com/forums/topic/205772-pong-tutorial/.
