#include "caption.h"
#include "message.h"
#include "compattr.h"
#include "gui.h"
#include <graphics.h>
#include <string.h>

TCaption::TCaption()
{
    isGraphical = 1;
    paintFunc = ((void(TObject::  *) (void)) (&TCaption::standardPaint));
    TCompAttr*  compAttr    = gui->colourScheme.getCompAttr();
    capLeftCol = compAttr->capLeftCol;
    capRightCol = compAttr->capRightCol;
    fontColour = compAttr->capFontColour;
    fontType = SMALL_FONT;
    fontSize = 4;
    cursor = gui->getCursor(CSR_MOVEMENT);
}

TCaption::~TCaption()
{
}

void TCaption::standardPaint()
{
    setfillstyle(SOLID_FILL, capLeftCol);
    bar(0, 0, size.x, size.y);
    setcolor(fontColour);
    settextstyle(fontType, HORIZ_DIR, fontSize);
    settextjustify(LEFT_TEXT, TOP_TEXT);
    outtextxy(3, 1, caption);
}

void TCaption::setCaption(char* nc)
{
    strcpy(caption, nc);
    if (active == 1)
    {
        TMessage    pmsg;
        pmsg.type = MSG_PAINT;
        addMessage(&pmsg);
    }
}

char* TCaption::getCaption()
{
    return caption;
}

void TCaption::handler()
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
    if (toHandle.type == MSG_PAINT)
    {
        paint();
    }
}















