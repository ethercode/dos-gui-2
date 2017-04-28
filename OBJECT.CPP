#include <graphics.h>
#include <mem.h>
#include "object.h"
#include "linklist.h"
#include "gui.h"
#include "standard.h"
#include "message.h"
#include "mouse.h"

TObject::TObject()
{
    active = 0;
    mouseState = MOUSE_OUTSIDE;
    child = new TLinkedList;
    message = new TStack;
    container = 0;
    isGraphical = 0;
    onClick = onPaint = onLeave = onEnter = onLeftUp = onLeftDown = onKeyPress = onActivate = 0;
    focusable = 1;
    TCompAttr*  compAttr    = gui->colourScheme.getCompAttr();
    fontColour = compAttr->fontColour;
    fontType = SMALL_FONT;
    fontSize = 4;
    standardShade[0] = compAttr->standardShade[0];
    standardShade[1] = compAttr->standardShade[1];
    standardShade[2] = compAttr->standardShade[2];
    standardShade[3] = compAttr->standardShade[3];
    cursor = gui->getCursor(CSR_STANDARD);
}

TObject::~TObject()
{
    if (child != 0)
    {
        delete child;
        child = 0;
    }
    if (message != 0)
    {
        delete message;
        message = 0;
    }
    if (container != 0)
    {
        container->removeChild(this);
    }
}

int TObject::isActive(void)
{
    return active;
}

void TObject::showMyCursor()
{
    cursor->show();
}

int TObject::totalChildren()
{
    if (active == 0)
    {
        return 0;
    }
    return child->total();
}

void TObject::handler(void)
{
}

TObject* TObject::getChild(int index)
{
    return child->get(index);
}

void TObject::activate(void)
{
    if (active == 0)
    {
        active = 1;
        TMessage    message;
        message.type = MSG_PAINT;
        addMessage(&message);
        if (onActivate != 0)
        {
            onActivate(this, 0);
        }
    }
}

void TObject::deactivate(void)
{
    if (active == 1)
    {
        active = 0;
        TMessage    message;
        message.type = MSG_PAINT;
        sendMessage(container, &message);
    }
}

void TObject::addChild(TObject* newChild)
{
    child->addItem(newChild);
    TMessage    message;
    message.type = MSG_PAINT;
    sendMessage(container, &message);
}

void TObject::deleteChild(TObject* oldChild)
{
    if (active == 0)
    {
        return;
    }
    child->deleteItem(oldChild);
    TMessage    message;
    message.type = MSG_PAINT;
    sendMessage(oldChild->container, &message);
}

void TObject::removeChild(TObject* oldChild)
{
    if (active == 0)
    {
        return;
    }
    child->unlistItem(oldChild);
    TMessage    message;
    message.type = MSG_PAINT;
    sendMessage(oldChild->container, &message);
}

TObject* TObject::getContainer()
{
    return container;
}

void TObject::changeContainer(TObject* newContainer)
{
    if (container != 0)
    {
        container->child->unlistItem(this);
        TMessage    message;
        message.type = MSG_PAINT;
        sendMessage(container, &message);
    }
    TMessage    message;
    message.type = MSG_PAINT;
    newContainer->addChild(this);
    container = newContainer;
    sendMessage(container, &message);
}

void TObject::sendMessage(TObject* target, TMessage* message)
{
    if (target->active == 0)
    {
        return;
    }
    if (target == 0)
    {
        return;
    }
    target->addMessage(message);
}

void TObject::treeSendMessage(TObject* where, TMessage* what, int sendHead)
{
    if (active == 0)
    {
        return;
    }
    TMessage    msg;
    msg.type = what->type;
    if (sendHead == 1)
    {
        sendMessage(where, &msg);
    }
    int a   = where->totalChildren();
    for (int b = 0; b < a; b++)
    {
        treeSendMessage(where->getChild(b), &msg, 1);
    }
}

void TObject::globalSendMessage(TMessage*)
{
    if (active == 0)
    {
        return;
    }
}

void TObject::addMessage(TMessage* toAdd)
{
    if (active == 0)
    {
        return;
    }
    if ((gui->mayIPaint() == 0) && (toAdd->type == MSG_PAINT))
    {
        return;
    }
    TMessage*   proxy   = new TMessage;
    memcpy(proxy, toAdd, sizeof(TMessage));
    message->addMessage(proxy);
}

int TObject::isFocused(void)
{
    if (gui->getKeyboard()->getFocused() == this)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void TObject::paint(void)
{
    if (isGraphical == 0)
    {
        return;
    }
    if (paintFunc == 0)
    {
        return;
    }
    TRect   vp;
    vp.x1 = getAbsoluteX();
    vp.y1 = getAbsoluteY();
    vp.x2 = vp.x1 + size.x;
    vp.y2 = vp.y1 + size.y;
    setviewport(vp.x1, vp.y1, vp.x2, vp.y2, 1);
    gui->hideMouse();
    (this->*paintFunc) ();
    gui->showMouse();
    setviewport(0, 0, 639, 479, 1);
}

void TObject::handleChildren()
{
    if (active == 0)
    {
        return;
    }
    int a   = totalChildren();
    int b;
    for (b = 0; b < a; b++)
    {
        TObject*childToHandle   = getChild(b);
        childToHandle->handler();
    }
}

int TObject::getAbsoluteX()
{
    TObject*desktop = gui->getDesktop();
    if (this == desktop)
    {
        return location.x;
    }
    else
    {
        return location.x + container->getAbsoluteX();
    }
}

int TObject::getAbsoluteY()
{
    TObject*desktop = gui->getDesktop();
    if (this == desktop)
    {
        return location.x;
    }
    else
    {
        return location.y + container->getAbsoluteY();
    }
}

TPoint* TObject::getLocation()
{
    return &location;
}

TPoint* TObject::getSize()
{
    return &size;
}

void TObject::setLocation(TPoint* newLocation)
{
    location.x = newLocation->x;
    location.y = newLocation->y;
    TMessage    pm;
    pm.type = MSG_PAINT;
    sendMessage(container, &pm);
}

void TObject::setSize(TPoint* newSize)
{
    size.x = newSize->x;
    size.y = newSize->y;
    TMessage    pm;
    pm.type = MSG_PAINT;
    sendMessage(container, &pm);
}

int TObject::whichChild(TObject* who)
{
    return child->where(who);
}

int TObject::mayFocus()
{
    return focusable;
}

void TObject::setFocusable(int k)
{
    if (k == 1)
    {
        focusable = 1;
    }
    if (k == 0)
    {
        focusable = 0;
    }
}

void TObject::focus()
{
    gui->getKeyboard()->setFocused(this);
}





