#ifndef _TIMER_
#define _TIMER_

#include "object.h"
#include "time.h"
#include "event.h"

class TTimer:public TObject
{
public:
            TTimer();
            ~TTimer();
    void    restart(void);
    void    handler();
    void    setInterval(int intervalTime);
    void    setEnabled(int enabledFlag);
    int     interval;
    int     enabled;
    TEvent  onTimer;
private:
    long    lastTime;
    clock_t start, end;
};

#endif