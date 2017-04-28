#ifndef _CPUMON_
#define _CPUMON_

#include "object.h"
#include "timer.h"

const   CPUTIME = 1;
const   CYCLES  = 2;

class TCPUMon:public TObject
{
public:
            TCPUMon();
            ~TCPUMon();
    void    handler();
    void    calculate(void);
private:
    int     standardColour[4];
    int     fontType, fontColour, fontSize;
    long    maxHandlers;
    long    handlers;
    TObject*updater;
    void    standardPaint(void);
    char    caption[26];
    int     showMode;
    void    setShowMode(int);
    float   ratio;
};


#endif