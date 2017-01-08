#include <lynx.h>
#include <tgi.h>
#include <6502.h> 
#include <joystick.h>
#include <stdlib.h>

extern void tgi_arialxy(int x, int y, char *msg);

void intro()
{
    while (tgi_busy()) {
    }
    tgi_clear();
    tgi_setcolor(COLOR_DARKGREY);
    tgi_bar(0, 0, 159, 101);
    tgi_setcolor(COLOR_LIGHTGREY);
    tgi_bar(4, 4, 159-4, 101-4);
    tgi_setcolor(COLOR_DARKBROWN);
    tgi_arialxy(7, 30, "  Push your mind to");
    tgi_arialxy(7, 42, "  the edge with the");
    tgi_arialxy(7, 54, "  power of Atari Lynx");
    tgi_updatedisplay();
    while (!joy_read(JOY_1))
        ;
}

