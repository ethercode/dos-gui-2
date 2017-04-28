#include "panel.h"
#include "compattr.h"
#include "gui.h"
#include <graphics.h>

TPanel::TPanel()
{
    isGraphical = 1;
    paintFunc = ((void(TObject::  *) (void)) (&TPanel::standardPaint));
    TCompAttr*  compAttr    = gui->colourScheme.getCompAttr();
    standardShade[0] = compAttr->standardShade[0];
    standardShade[1] = compAttr->standardShade[1];
    standardShade[2] = compAttr->standardShade[2];
    standardShade[3] = compAttr->standardShade[3];
}

TPanel::~TPanel()
{
}

void TPanel::handler()
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
    if (toHandle.type == MSG_UPDATECOLOURS)
    {
        TCompAttr*  compAttr    = gui->colourScheme.getCompAttr();
        standardShade[0] = compAttr->standardShade[0];
        standardShade[1] = compAttr->standardShade[1];
        standardShade[2] = compAttr->standardShade[2];
        standardShade[3] = compAttr->standardShade[3];
    }
    if (toHandle.type == MSG_PAINT)
    {
        paint();
        if (onPaint != 0)
        {
            onPaint(this, 0);
        }
        treeSendMessage(this, &toHandle, 0);
    }
    handleChildren();
}

void TPanel::standardPaint()
{
    setfillstyle(SOLID_FILL, standardShade[1]);
    bar(0, 0, size.x, size.y);
    setcolor(standardShade[1]);
    line(0, 0, size.x - 1, 0);
    line(0, 0, 0, size.y - 1);
    setcolor(standardShade[0]);
    line(1, 1, size.x - 2, 1);
    line(1, 1, 1, size.y - 2);
    setcolor(standardShade[3]);
    line(size.x, size.y, size.x, 0);
    line(size.x, size.y, 0, size.y);
    setcolor(standardShade[2]);
    line(size.x - 1, size.y - 1, size.x - 1, 1);
    line(size.x - 1, size.y - 1, 1, size.y - 1);
}

