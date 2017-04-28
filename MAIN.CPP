//extern _stklen = 32000;

#include "gui.h"

TGui*   gui;

int main(void)
{
    gui = new TGui;
    gui->execute();
    delete gui;
    return 0;
}
