#include "api.h"
#include "object.h"
#include "desktop.h"
#include "timer.h"
#include "button.h"
#include "panel.h"
#include <string.h>
#include "caption.h"
#include "cpumon.h"
#include "gui.h"

TObject* createButton(TObject* cont, int x, int y, int w, int h, int f, char* ttl)
{
    TObject*button  = new TButton;
    TPoint  loc, size;
    loc.x = x;
    loc.y = y;
    button->setLocation(&loc);
    size.x = w;
    size.y = h;
    button->setSize(&size);
    button->changeContainer(cont);
    strcpy(((TButton *) (button))->getCaption(), ttl);
    ((TButton *) (button))->setFlat(f);
    button->activate();
    return button;
}

TObject* createPanel(TObject* cont, int x, int y, int w, int h)
{
    TObject*panel   = new TPanel;
    TPoint  loc, size;
    loc.x = x;
    loc.y = y;
    panel->setLocation(&loc);
    size.x = w;
    size.y = h;
    panel->setSize(&size);
    panel->changeContainer(cont);
    panel->activate();
    return panel;
}

TObject* createTimer(TObject* cont, int iv, int en)
{
    TTimer* t   = new TTimer;
    t->changeContainer(cont);
    t->setInterval(iv);
    t->setEnabled(en);
    t->activate();
    return t;
}

TObject* createCaption(TObject* cont, int x, int y, int w, int h, char* cap)
{
    TObject*caption = new TCaption;
    caption->changeContainer(cont);
    TPoint  p;
    p.x = x;
    p.y = y;
    caption->setLocation(&p);
    p.x = w;
    p.y = h;
    caption->setSize(&p);
    ((TCaption *) (caption))->setCaption(cap);
    caption->activate();
    return caption;
}

TObject* createCPUMon(TObject* cont, int x, int y, int w, int h)
{
    TObject*cpumon  = new TCPUMon;
    cpumon->changeContainer(cont);
    TPoint  p;
    p.x = x;
    p.y = y;
    cpumon->setLocation(&p);
    p.x = w;
    p.y = h;
    cpumon->setSize(&p);
    cpumon->activate();
    return cpumon;
}