#include "timer.h"
#include "api.h"
#include <graphics.h>
#include <stdlib.h>
#include "object.h"
#include <conio.h>
#include "gui.h"
#include "desktop.h"
#include "event.h"
#include "keyboard.h"
#include <process.h>
#include "button.h"

int     dir = 0;

TObject*panel3;
TObject*cpu;

void togCpu(TObject* sender, void*)
{
    static int  vis = 1;
    if (vis == 1)
    {
        cpu->deactivate();
        ((TButton *) (sender))->setCaption("Show cpu-mon");
    }
    else
    {
        cpu->activate();
        ((TButton *) (sender))->setCaption("Hide cpu-mon");
    }
    vis = 1 - vis;
}

void togCol(TObject* sender, void*)
{
    static int  vis = 1;
    if (vis == 1)
    {
        panel3->deactivate();
        ((TButton *) (sender))->setCaption("Show colourer");
    }
    else
    {
        panel3->activate();
        ((TButton *) (sender))->setCaption("Hide colourer");
    }
    vis = 1 - vis;
}

void changeBouncy(TObject*, void*)
{
    dir = -dir;
    if (dir == 0)
    {
        dir = 1;
    }
}

void mover(TObject* sender, void*)
{
    TPoint* loc = sender->getContainer()->getLocation();
    if (dir == 0)
    {
        return;
    }
    if ((dir == 1) && (loc->y > 270))
    {
        return;
    }
    if ((dir == -1) && (loc->y < 6))
    {
        return;
    }
    TPoint  loca;
    loca.x = loc->x;
    loca.y = loc->y + dir * 2;
    sender->getContainer()->setLocation(&loca);
}

void setNorm(TObject*, void*)
{
    gui->colourScheme.setPredefined(SCHEME_STANDARD);
}

void setSky(TObject*, void*)
{
    gui->colourScheme.setPredefined(SCHEME_SKY);
}

void quit(TObject*, void*)
{
    gui->stopGui();
}


void makeStuff(void)
{
    gui->disallowPainting();
    cpu = createCPUMon(gui->getDesktop(), 600, 0, 39, 479);
    panel3 = createPanel(gui->getDesktop(), 10, 300, 210, 45);
    TObject*panel   = createPanel(gui->getDesktop(), 10, 10, 90, 195);
    createButton(panel, 10, 10, 70, 25, 0, "Button #1");
    createButton(panel, 10, 40, 70, 25, 0, "Button #2");
    createButton(panel, 10, 70, 70, 25, 0, "Button #3");
    createButton(panel, 10, 100, 70, 25, 0, "Button #4");
    createButton(panel, 10, 130, 70, 25, 0, "Button #5");
    createButton(panel, 10, 160, 70, 25, 0, "Button #6");
    TObject*panel2  = createPanel(gui->getDesktop(), 130, 10, 90, 195);
    createButton(panel2, 10, 10, 70, 25, 1, "Button #7");
    createButton(panel2, 10, 40, 70, 25, 1, "Button #8");
    createButton(panel2, 10, 70, 70, 25, 1, "Button #9");
    createButton(panel2, 10, 100, 70, 25, 1, "Button #10");
    createButton(panel2, 10, 130, 70, 25, 1, "Button #11");
    createButton(panel2, 10, 160, 70, 25, 1, "Button #12");
    TObject*b1  = createButton(panel3, 10, 10, 90, 25, 0, "Normal scheme");
    TObject*b2  = createButton(panel3, 110, 10, 90, 25, 0, "'Sky' Scheme");
    b1->onClick = setNorm;
    b2->onClick = setSky;
    TObject*but = createButton(gui->getDesktop(), 5, 450, 90, 25, 0, "Quit!");
    but->onClick = quit;
    TObject*panel4  = createPanel(gui->getDesktop(), 330, 10, 100, 300);
    TObject*but2    = createButton(panel4, 5, 5, 90, 25, 0, "Click me!");
    TObject*tim     = createTimer(but2, 100, 1);
    ((TTimer *) (tim))->onTimer = mover;
    but2->onClick = changeBouncy;
    gui->allowPainting();
    TObject*panel5  = createPanel(gui->getDesktop(), 10, 375, 210, 45);
    TObject*b3      = createButton(panel5, 10, 10, 90, 25, 0, "Hide cpu-mon");
    TObject*b4      = createButton(panel5, 110, 10, 90, 25, 0, "Hide colourer");
    b3->onClick = togCpu;
    b4->onClick = togCol;
}

TGui::TGui()
{
    mustExit = 0;
    randomize();
    mouse = 0;
    graphicsOn = 0;
    desktop = 0;
    canPaint = 1;
}

TGui::~TGui()
{
    delete mouse;
    delete keyboard;
    setText();
}

TCursor* TGui::getCursor(int a)
{
    return mouse->getCursor(a);
}

void TGui::disallowPainting()
{
    canPaint = 0;
}

void TGui::allowPainting()
{
    canPaint = 1;
    TMessage    pmsg;
    pmsg.type = 1;
    desktop->treeSendMessage(desktop, &pmsg, 1);
}

void TGui::setGraphics(void)
{
    if (graphicsOn == 1)
    {
        return;
    }
    int a   = VGA;
    int b   = VGAHI;
    initgraph(&a, &b, "drivers");
    graphicsOn = 1;
}

void TGui::setText()
{
    if (graphicsOn == 0)
    {
        return;
    }
    closegraph();
    graphicsOn = 0;
}

void TGui::execute()
{
    init();
    loop();
    exit();
}

void TGui::init()
{
    setGraphics();
    mouse = new TMouse;
    keyboard = new TKeyboard;
    desktop = new TDesktop;
    desktop->activate();
}

void setStandard(TObject* sender)
{
    sender;
    gui->colourScheme.setPredefined(SCHEME_STANDARD);
}

void setSky(TObject* sender)
{
    sender;
    gui->colourScheme.setPredefined(SCHEME_SKY);
}

void TGui::loop()
{
    TObject*desktop = gui->getDesktop();
    while (!mustExit)
    {
        mouse->handler();
        keyboard->handler();
        desktop->handler();
        static int  h   = 0;
        if (h == 0)
        {
            makeStuff();
            h = 1;
        }
    }
}

void TGui::exit()
{
    delete desktop;
}

void TGui::stopGui()
{
    mustExit = 1;
}

TObject* TGui::getDesktop(void)
{
    return desktop;
}

void TGui::showMouse()
{
    mouse->show();
}

void TGui::hideMouse()
{
    mouse->hide();
}

TMouse* TGui::getMouse()
{
    return mouse;
}

TKeyboard* TGui::getKeyboard()
{
    return keyboard;
}

int TGui::mayIPaint()
{
    return canPaint;
}
