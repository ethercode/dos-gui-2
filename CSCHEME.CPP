#include <graphics.h>
#include "cscheme.h"
#include <memory.h>
#include "gui.h"
#include "message.h"
#include "desktop.h"

TColourScheme::TColourScheme()
{
    constructing = 1;
    setPredefined(SCHEME_STANDARD);
    constructing = 0;
}

TCompAttr* TColourScheme::getCompAttr()
{
    return &compAttr;
}

void TColourScheme::setPredefined(int num)
{
    if (num == SCHEME_STANDARD)
    {
        compAttr.capLeftCol = BLUE;
        compAttr.capRightCol = LIGHTBLUE;
        compAttr.standardShade[0] = WHITE;
        compAttr.standardShade[1] = LIGHTGRAY;
        compAttr.standardShade[2] = DARKGRAY;
        compAttr.standardShade[3] = BLACK;
        compAttr.fontColour = BLACK;
        compAttr.desktopColour = CYAN;
        compAttr.capFontColour = WHITE;
    }
    if (num == SCHEME_SKY)
    {
        compAttr.capLeftCol = CYAN;
        compAttr.capRightCol = LIGHTCYAN;
        compAttr.standardShade[0] = WHITE;
        compAttr.standardShade[1] = LIGHTBLUE;
        compAttr.standardShade[2] = BLUE;
        compAttr.standardShade[3] = BLACK;
        compAttr.desktopColour = LIGHTGRAY;
        compAttr.fontColour = WHITE;
        compAttr.capFontColour = BLACK;
    }
    if (constructing == 0)
    {
        applyScheme();
    }
}

void TColourScheme::setCompAttr(TCompAttr* nAttr)
{
    memcpy(&compAttr, nAttr, sizeof(TCompAttr));
    applyScheme();
}

void TColourScheme::applyScheme()
{
    TMessage    updMsg;
    updMsg.type = MSG_UPDATECOLOURS;
    gui->getDesktop()->treeSendMessage(gui->getDesktop(), &updMsg, 1);
    TMessage    pMsg;
    pMsg.type = MSG_PAINT;
    gui->getDesktop()->treeSendMessage(gui->getDesktop(), &pMsg, 1);
}


