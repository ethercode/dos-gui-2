#include "desktop.h"
#include <mem.h>
#include "mstack.h"
#include "appfuncs.h"
#include <graphics.h>
#include "gui.h"

void focusSender(TObject* sender, void*)
{
    sender->focus();
}

TDesktop::TDesktop()
{
    cursor = gui->getCursor(CSR_EZGUI);
    showMyCursor();
    isGraphical = 1;
    location.x = 0;
    location.y = 0;
    size.x = 639;
    size.y = 479;
    colour = gui->colourScheme.getCompAttr()->desktopColour;;
    paintFunc = ((void(TObject::  *) (void)) (&TDesktop::standardPaint));
    onActivate = focusSender;
}

TDesktop::~TDesktop()
{
}

void TDesktop::standardPaint()
{
    setfillstyle(SOLID_FILL, colour);
    bar(location.x, location.y, location.x + size.x, location.y + size.y);
}

void TDesktop::handler()
{
    //message
    if (active == 0)
    {
        return;
    }
    TMessage*   m   = message->getItem();
    if (m != 0)
    {
        TMessage    toHandle;
        memcpy(&toHandle, m, sizeof(TMessage));
        delete m;
        if (toHandle.type == MSG_UPDATECOLOURS)
        {
            colour = gui->colourScheme.getCompAttr()->desktopColour;;
        }
        if (toHandle.type == MSG_PAINT)
        {
            paint();
            TMessage    paintmsg;
            paintmsg.type = MSG_PAINT;
            treeSendMessage(this, &paintmsg, 0);
        }
        if (toHandle.type == MSG_KEYPRESS)
        {
            if (onKeyPress != 0)
            {
                onKeyPress(this, toHandle.keyPress);
            }
        }
    }
    handleChildren();
}
