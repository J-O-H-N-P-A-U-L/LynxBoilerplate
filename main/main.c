#include <lynx.h>
#include <tgi.h>
#include <6502.h> 
#include <joystick.h>
#include <stdlib.h>

void lynx_snd_init ();
void lynx_snd_pause ();
void lynx_snd_continue ();
void __fastcall__ lynx_snd_play (unsigned char channel, unsigned char *music);
void lynx_snd_stop ();

extern void intro();
extern void play();

typedef struct {
    unsigned char *music0;
    unsigned char *music1;
    unsigned char *music2;
    unsigned char *music3;
} song_t;

extern song_t musicptr;

#define MAIN_FILENR 0
#define game_FILENR 1
#define POPCORN_FILENR 2
#define INTRO_FILENR 3

void main()
{
  joy_install(&lynx_stdjoy);
  tgi_install(&lynx_160_102_16);
  tgi_init();
  tgi_setcollisiondetection(1);
  lynx_snd_init();
  CLI();
  while (1) {
    lynx_load(INTRO_FILENR);
    intro();

    lynx_snd_pause();
    lynx_load(POPCORN_FILENR);
    lynx_snd_play(0, musicptr.music0);
    lynx_snd_play(1, musicptr.music1);
    lynx_snd_play(2, musicptr.music2);
    lynx_snd_play(3, musicptr.music3);
    lynx_snd_continue();

    lynx_load(game_FILENR);
    play();
  }
}

