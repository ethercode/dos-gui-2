#include "cursor.h"
#include "gui.h"
#include <math.h>
#include <stdio.h>

TCursor::TCursor(char* fil, int x, int y)
{
    FILE*   file;
    file = fopen(fil, "rb");
    char    c;
    int     a, b;
    for (a = 0; a < 16; a++)
    {
        data[a] = 0;
        data[a + 16] = 0;
        for (b = 0; b < 16; b++)
        {
            fread(&c, 1, 1, file);
            if (c == '0')
            {
                data[a] += (pow(2, 15 - b));
            }
            if (c == '1')
            {
                data[a + 16] += (pow(2, 15 - b));
            }
            if (c == '3')
            {
                data[a] += (pow(2, 15 - b));
                data[a + 16] += (pow(2, 15 - b));
            }
        }
        fread(&c, 1, 1, file);
        fread(&c, 1, 1, file);
    }
    fclose(file);
    hx = x;
    hy = y;
}

void TCursor::show()
{
    static TCursor* currentCursor;
    if (currentCursor == this)
    {
        return;
    }
    currentCursor = this;
    unsigned long k = ((unsigned long) (data));
    unsigned int s = unsigned((k & 0xFFFF0000L) >> 16),
    o = unsigned(k & 0x0000FFFFL);
    gui->getMouse()->hide();
    unsigned int x = hx,y = hy;
    asm {
        mov ax,9
        mov bx,x;
        mov cx,y;
        mov dx,s;
        mov es,dx;
        mov dx,o;
        int 0x33;
    }
    gui->getMouse()->show();
}
