#include "button.h"
#include "mstack.h"
#include "cscheme.h"
#include "gui.h"
#include "standard.h"
#include <graphics.h>
#include <string.h>
#include "compAttr.h"
#include "message.h"

void enter(TObject* sender, void* keyPress)
{
    unsigned char scancode = ((unsigned char *) (keyPress))[0];
    unsigned char extended = ((unsigned char *) (keyPress))[1];
    if ((scancode == 13) && (extended == 0))
    {
        TMessage    clickMessage;
        clickMessage.type = MSG_MOUSE_LEFT_CLICK;
        sender->addMessage(&clickMessage);
    }
}

TButton::TButton()
{
    isGraphical = 1;
    paintFunc = ((void(TObject::  *) (void)) (&TButton::flatPaint));
    TCompAttr*  compAttr    = gui->colourScheme.getCompAttr();
    standardShade[0] = compAttr->standardShade[0];
    standardShade[1] = compAttr->standardShade[1];
    standardShade[2] = compAttr->standardShade[2];
    standardShade[3] = compAttr->standardShade[3];
    fontColour = compAttr->fontColour;
    fontType = SMALL_FONT;
    fontSize = 4;
    isDown = 0;
    flat = 1;
    this->onKeyPress = enter;
}

TButton::~TButton()
{
    delete caption;
}

void TButton::setFlat(int flatness)
{
    if (flatness == flat)
    {
        return;
    }
    flat = flatness;
    if (flat == 1)
    {
        if (isDown == 0)
        {
            paintFunc = ((void(TObject::  *) (void)) (&TButton::flatPaint));
        }
        else
        {
            paintFunc = ((void(TObject::  *) (void)) (&TButton::downPaint));
        }
    }
    else
    {
        if (isDown == 0)
        {
            paintFunc = ((void(TObject::  *) (void)) (&TButton::upPaint));
        }
        else
        {
            paintFunc = ((void(TObject::  *) (void)) (&TButton::downPaint));
        }
    }
    TMessage    msg;
    msg.type = MSG_PAINT;
    addMessage(&msg);
}

void TButton::drawFocusBlock()
{
    int a   = isFocused();
    if (a == 0)
    {
        return;
    }
    setlinestyle(USERBIT_LINE, 21845, 1);
    setcolor(standardShade[3]);
    rectangle(3, 3, size.x - 3, size.y - 3);
    setlinestyle(SOLID_LINE, 0, 1);
}

void TButton::flatPaint()
{
    setfillstyle(SOLID_FILL, standardShade[1]);
    bar(0, 0, size.x, size.y);
    setcolor(fontColour);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(fontType, HORIZ_DIR, fontSize);
    outtextxy(size.x / 2, size.y / 2, caption);
    drawFocusBlock();
}

void TButton::upPaint()
{
    setfillstyle(SOLID_FILL, standardShade[1]);
    bar(0, 0, size.x, size.y);
    setcolor(standardShade[0]);
    line(1, 1, size.x, 1);
    line(1, 1, 1, size.y);
    setcolor(standardShade[3]);
    line(size.x, size.y, size.x, 0);
    line(size.x, size.y, 0, size.y);
    setcolor(standardShade[2]);
    line(size.x - 1, size.y - 1, size.x - 1, 1);
    line(size.x - 1, size.y - 1, 1, size.y - 1);
    setcolor(fontColour);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(fontType, HORIZ_DIR, fontSize);
    outtextxy(size.x / 2, size.y / 2, caption);
    drawFocusBlock();
}

void TButton::downPaint()
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
    outtextxy(size.x / 2 + 1, size.y / 2 + 1, caption);
    drawFocusBlock();
}

void TButton::handler()
{
    if (active == 0)
    {
        return;
    }
    TMessage*   m   = message->getItem();
    if (m == 0)
    {
        m->type = MSG_NULL;
    }
    if (m->type == MSG_UPDATECOLOURS)
    {
        TCompAttr*  compAttr    = gui->colourScheme.getCompAttr();
        standardShade[0] = compAttr->standardShade[0];
        standardShade[1] = compAttr->standardShade[1];
        standardShade[2] = compAttr->standardShade[2];
        standardShade[3] = compAttr->standardShade[3];
        fontColour = compAttr->fontColour;
    }
    if (m->type == MSG_PAINT)
    {
        paint();
        if (onPaint != 0)
        {
            onPaint(this, 0);
        }
        treeSendMessage(this, m, 0);
    }
    if (m->type == MSG_MOUSE_ENTER)
    {
        if (flat == 1)
        {
            paintFunc = ((void(TObject::  *) (void)) (&TButton::upPaint));
            TMessage    msg;
            msg.type = MSG_PAINT;
            addMessage(&msg);
        }
        if (onEnter != 0)
        {
            onEnter(this, 0);
        }
    }
    if (m->type == MSG_MOUSE_LEAVE)
    {
        if (flat == 1)
        {
            paintFunc = ((void(TObject::  *) (void)) (&TButton::flatPaint));
            TMessage    msg;
            msg.type = MSG_PAINT;
            addMessage(&msg);
        }
        else if (isDown == 1)
        {
            paintFunc = ((void(TObject::  *) (void)) (&TButton::upPaint));
            TMessage    msg;
            msg.type = MSG_PAINT;
            addMessage(&msg);
        }
        if (onLeave != 0)
        {
            onPaint(this, 0);
        }
        isDown = 0;
    }
    if (m->type == MSG_MOUSE_LEFT_DOWN)
    {
        isDown = 1;
        paintFunc = ((void(TObject::  *) (void)) (&TButton::downPaint));
        TMessage    msg;
        msg.type = MSG_PAINT;
        addMessage(&msg);
        if (onLeftDown != 0)
        {
            onLeftDown(this, 0);
        }
    }
    if (m->type == MSG_MOUSE_LEFT_UP)
    {
        if (isDown == 1)
        {
            isDown = 0;
            paintFunc = ((void(TObject::  *) (void)) (&TButton::upPaint));
            TMessage    msg;
            msg.type = MSG_PAINT;
            addMessage(&msg);
            TMessage    click;
            click.type = MSG_MOUSE_LEFT_CLICK;
            addMessage(&click);
            if (onLeftUp != 0)
            {
                onLeftUp(this, 0);
            }
        }
    }
    if (m->type == MSG_MOUSE_LEFT_CLICK)
    {
        if (onClick != 0)
        {
            onClick(this, 0);
        }
    }
    if (m->type == MSG_KEYPRESS)
    {
        if (onKeyPress != 0)
        {
            onKeyPress(this, m->keyPress);
        }
    }
    if ((m->type == MSG_FOCUS_LOST) || (m->type == MSG_FOCUS_GAINED))
    {
        TMessage    msg;
        msg.type = MSG_PAINT;
        addMessage(&msg);
    }
    delete m;
    handleChildren();
}

void TButton::setCaption(char* newCaption)
{
    strcpy(caption, newCaption);
    TMessage    msg;
    msg.type = MSG_PAINT;
    addMessage(&msg);
}

char* TButton::getCaption()
{
    return caption;
}
