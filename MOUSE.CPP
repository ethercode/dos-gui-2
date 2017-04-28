#include "mouse.h"
#include "object.h"
#include "linklist.h"
#include "object.h"
#include "gui.h"

TObject* TMouse::checkObject(TObject* obj)
{
    if (obj->isActive() == 0)
    {
        return 0;
    }
    TRect   reg;
    reg.x1 = obj->getAbsoluteX();
    reg.y1 = obj->getAbsoluteY();
    reg.x2 = reg.x1 + obj->getSize()->x;
    reg.y2 = reg.y1 + obj->getSize()->y;
    if (checkInside(&reg) == 1)
    {
        int a   = obj->totalChildren();
        if (a > 0)
        {
            int     i       = 0;
            TObject*found   = 0;
            while ((found == 0) && (i < a))
            {
                found = checkObject(obj->getChild(i));
                if ((found == 0) && (i == a - 1))
                {
                    found = obj;
                }
                i++;
            }
            return found;
        }
        else
        {
            return obj;
        }
    }
    else
    {
        return 0;
    }
}

void TMouse::handler(void)
{
    update();
    TObject*desktop = gui->getDesktop();
    pointed = checkObject(desktop);
    createMouseEvents();
}

int TMouse::getLeftDown()
{
    return leftDown;
}

void TMouse::loadCursors()
{
    cursor[0] = new TCursor("cursors\\std.cur", 0, 0);
    cursor[1] = new TCursor("cursors\\move.cur", 8, 8);
    cursor[2] = new TCursor("cursors\\disabled.cur", 8, 8);
    cursor[3] = new TCursor("cursors\\ezgui.cur", 1, 14);
}

TCursor* TMouse::getCursor(int a)
{
    return cursor[a];
}

int TMouse::getRightDown()
{
    return rightDown;
}

void TMouse::createMouseEvents()
{
    static TObject* oldPointed  = 0;
    pointed = gui->getMouse()->getPointed();
    if (oldPointed == 0)
    {
        TMessage    msg;
        msg.type = MSG_MOUSE_ENTER;
        sendMessage(pointed, &msg);
    }
    else
    {
        if (pointed != oldPointed)
        {
            TMessage    msg;
            msg.type = MSG_MOUSE_LEAVE;
            sendMessage(oldPointed, &msg);
            TMessage    msg2;
            msg2.type = MSG_MOUSE_ENTER;
            sendMessage(pointed, &msg2);
            pointed->showMyCursor();
        }
    }
    oldPointed = pointed;
    if ((oldLeftDown == 0) && (leftDown == 1))
    {
        TMessage    bd;
        bd.type = MSG_MOUSE_LEFT_DOWN;
        if (pointed->mayFocus() == 1)
        {
            gui->getKeyboard()->setFocused(pointed);
        }
        sendMessage(pointed, &bd);
    }
    if ((oldLeftDown == 1) && (leftDown == 0))
    {
        TMessage    bd;
        bd.type = MSG_MOUSE_LEFT_UP;
        sendMessage(pointed, &bd);
    }
}

TMouse::TMouse()
{
    visible = 0;
    asm
    {
        mov ax,0x0007
        mov cx,0;
        mov dx,639;
        int 0x33;
        mov ax,0x0008
        mov cx,0;
        mov dx,479;
        int 0x33;
    }
    setMousePosition(319, 239);
    leftDown = 0;
    rightDown = 0;
    show();
    pointed = 0;
    loadCursors();
}

TMouse::~TMouse()
{
    hide(0, 0, 639, 479);
    delete cursor[0];
    delete cursor[1];
    delete cursor[2];
    delete cursor[3];
}


void TMouse::show()
{
    if (!visible)
    {
        visible = 1;
        asm
        {
            mov ax,0x0001;
            int 0x33;
        }
    }
}

int TMouse::checkInside(TRect* rec)
{
    int x1  = rec->x1;
    int y1  = rec->y1;
    int x2  = rec->x2;
    int y2  = rec->y2;
    if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void TMouse::hide(int x1, int y1, int x2, int y2)
{
    if (visible)
    {
        update();
        if ((x > x1) && (x < x2) && (y > y1) && (y < y2))
        {
            visible = 0;
            asm
            {
                mov ax,0x0002;
                int 0x33;
            }
        }
    }
}

void TMouse::hide()
{
    if (visible)
    {
        {
            visible = 0;
            asm
            {
                mov ax,0x0002;
                int 0x33;
            }
        }
    }
}

void TMouse::setMousePosition(int x, int y)
{
    asm
    {
        mov ax,0x0004
        mov cx,x;
        mov dx,y;
        int 0x33;
    }
}

void TMouse::update()
{
    unsigned int xPos,yPos,bState;
    asm
    {
        mov ax,0x0003
        int 0x33
        mov bState,bx
        mov xPos,cx
        mov yPos,dx
    }
    if (bState == 0)
    {
        oldLeftDown = leftDown;
        leftDown = 0;
        oldRightDown = rightDown;
        rightDown = 0;
    }
    if (bState == 1)
    {
        oldLeftDown = leftDown;
        leftDown = 1;
    }
    if (bState == 2)
    {
        oldRightDown = rightDown;
        rightDown = 1;
    }
    if (bState == 3)
    {
        oldLeftDown = leftDown;
        leftDown = 1;
        oldRightDown = rightDown;
        rightDown = 1;
    }
    x = xPos;
    y = yPos;
}

TObject* TMouse::getPointed()
{
    return pointed;
}





