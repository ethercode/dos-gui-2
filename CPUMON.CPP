#include "cpumon.h"
#include "compattr.h"
#include <graphics.h>
#include "api.h"
#include <stdio.h>
#include "gui.h"

void contPainter(TObject* sender, void*)
{
    ((TCPUMon *) (sender->getContainer()))->calculate();
    TMessage    pm;
    pm.type = MSG_PAINT;
    sender->sendMessage(sender->getContainer(), &pm);
}

void TCPUMon::calculate()
{
    if (handlers == 0)
    {
        return;
    }
    if (maxHandlers < handlers)
    {
        maxHandlers = handlers;
    }
    float   q   = float(maxHandlers - handlers) / float(maxHandlers);
    ratio = q;
    q *= 100.0;
    if (showMode == CYCLES)
    {
        sprintf(caption, "%ld\\%ld", handlers, maxHandlers);
    }
    if (showMode == CPUTIME)
    {
        sprintf(caption, "%3.2f", q);
    }
    handlers = 0;
}

TCPUMon::TCPUMon()
{
    showMode = CPUTIME;
    caption[0] = 0;
    isGraphical = 1;
    paintFunc = ((void(TObject::  *) (void)) (&TCPUMon::standardPaint));
    updater = createTimer(this, 1000, 1);
    ((TTimer *) (updater))->onTimer = contPainter;
    maxHandlers = handlers = 0;
    TCompAttr*  compAttr    = gui->colourScheme.getCompAttr();
    fontColour = compAttr->fontColour;
    fontType = SMALL_FONT;
    fontSize = 4;
}

TCPUMon::~TCPUMon()
{
    delete updater;
}

void TCPUMon::handler()
{
    if (active == 0)
    {
        return;
    }
    TMessage*   m   = message->getItem();
    TMessage    toHandle;
    toHandle.type = m->type;
    delete m;
    if (m == 0)
    {
        toHandle.type = MSG_NULL;
    }
    handlers++;
    if (toHandle.type == MSG_PAINT)
    {
        paint();
    }
    if (toHandle.type == MSG_UPDATECOLOURS)
    {
        TCompAttr*  compAttr    = gui->colourScheme.getCompAttr();
        standardShade[0] = compAttr->standardShade[0];
        standardShade[1] = compAttr->standardShade[1];
        standardShade[2] = compAttr->standardShade[2];
        standardShade[3] = compAttr->standardShade[3];
        fontColour = compAttr->fontColour;
    }
    handleChildren();
}

void TCPUMon::standardPaint()
{
    setfillstyle(SOLID_FILL, standardShade[1]);
    bar(1, 1, size.x - 1, size.y - 1);
    setcolor(standardShade[3]);
    line(1, 1, size.x, 1);
    line(1, 1, 1, size.y);
    setcolor(standardShade[2]);
    line(0, 0, size.x, 0);
    line(0, 0, 0, size.y);
    setcolor(standardShade[0]);
    line(size.x, size.y, size.x, 0);
    line(size.x, size.y, 0, size.y);
    setcolor(fontColour);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(fontType, HORIZ_DIR, fontSize);
    if ((ratio >= 0.00) && (ratio <= 1.00))
    {
        int y   = size.y - float(size.y - 4) * ratio - 2;
        setfillstyle(SOLID_FILL, standardShade[2]);
        bar(size.x - 2, size.y - 2, 2, y);
        outtextxy(size.x / 2 + 1, size.y / 2 + 1, caption);
    }
}










