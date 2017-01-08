#include <lynx.h>
#include <tgi.h>
#include <6502.h> 
#include <joystick.h>
#include <stdlib.h>

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

unsigned char ball[] = {
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  0
};

unsigned char wall[] = {
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  2, 0x7E,
  0
};

typedef struct {
  char collindex;
  SCB_REHV sprite;
  PENPAL_1;
  signed char hvel;
  signed char vvel;
} sprite_t;

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

void play()
{
  unsigned char joy;
  char buffer[16];
  signed RightScore = 0;
  signed LeftScore = 0;
  signed char vol = 120;
  unsigned char chan = 0;

  while (1) {
    while (tgi_busy()) {
    //asm("lda $fd22");
    //asm("sta $fdb0");
    //asm("lda $fd32");
    //asm("sta $fda0");
  }
    /* Erase collision buffer */
    tgi_clear();
    LeftPaddle.penpal[0] = COLOR_GREY;
    RightPaddle.penpal[0] = COLOR_GREY;

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
    if (Ball.sprite.hpos > 80) {
        if (Ball.sprite.vpos > RightPaddle.sprite.vpos) {
            RightPaddle.sprite.vpos++;
        } else {
            RightPaddle.sprite.vpos--;
        }
    }

    /* Paint stationary sprites */
    tgi_sprite(&TopWall.sprite);
    tgi_sprite(&BottomWall.sprite);
    tgi_sprite(&LeftPaddle.sprite);
    tgi_sprite(&RightPaddle.sprite);

    /* Draw last collidable sprite */
    tgi_sprite(&Ball.sprite);

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
    tgi_setcolor(COLOR_WHITE);
    itoa(LeftScore, &buffer[0], 10);
    tgi_outtextxy(40, 10, buffer);
    itoa(RightScore, &buffer[0], 10);
    tgi_outtextxy(120, 10, buffer);
    tgi_updatedisplay();
  }
}

