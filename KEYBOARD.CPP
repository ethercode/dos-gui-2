#include "keyboard.h"
#include "gui.h"
#include "object.h"
#include <conio.h>

TKeyboard::TKeyboard()
{
    focused = 0;
}

TKeyboard::~TKeyboard()
{
}

TObject* TKeyboard::getFocused()
{
    return focused;
}

void TKeyboard::handler(void)
{
    if (kbhit())
    {
        TMessage    kpmsg;
        kpmsg.type = MSG_KEYPRESS;
        unsigned char scancode = getch();
        unsigned char extended = 0;
        if (scancode == 0)
        {
            extended = 1;
            scancode = getch();
        }
        kpmsg.keyPress[0] = scancode;
        kpmsg.keyPress[1] = extended;
        int syskey  = 0;
        if ((scancode == 9) && (extended == 0))
        {
            focusNext();
            syskey = 1;
        }
        if ((scancode == 15) && (extended == 1))
        {
            focusPrev();
            syskey = 1;
        }
        if (syskey == 0)
        {
            sendMessage(focused, &kpmsg);
        }
    }
}

void TKeyboard::setFocused(TObject* newFocused)
{
    if (focused == newFocused)
    {
        return;
    }
    if (focused != 0)
    {
        TMessage    lostFocusMessage;
        lostFocusMessage.type = MSG_FOCUS_LOST;
        sendMessage(focused, &lostFocusMessage);
    }
    TMessage    gainedFocusMessage;
    gainedFocusMessage.type = MSG_FOCUS_GAINED;
    focused = newFocused;
    sendMessage(focused, &gainedFocusMessage);
}

void TKeyboard::focusNext()
{
    if (focused == gui->getDesktop())
    {
        return;
    }
    TObject*cont    = focused->getContainer();
    int     a       = cont->totalChildren();
    if (a == 1)
    {
        return;
    }
    int b   = cont->whichChild(focused);
    if (b < 0)
    {
        return;
    }
    int c   = b + 1;
    if (c >= a)
    {
        c = 0;
    }
    TObject*object  = cont->getChild(c);
    setFocused(object);
}

void TKeyboard::focusPrev()
{
}

