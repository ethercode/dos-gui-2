#include "timer.h"
#include "time.h"
#include "message.h"

TTimer::TTimer()
{
    isGraphical = 0;
    interval = 1000;
    enabled = 0;
    start = clock();
    restart();
    onTimer = 0;
}

TTimer::~TTimer()
{
}

void TTimer::restart()
{
    lastTime = time(0);
}

void TTimer::setEnabled(int enabledFlag)
{
    enabled = enabledFlag;
    lastTime = time(0);
}

void TTimer::setInterval(int intervalTime)
{
    interval = intervalTime;
}

void TTimer::handler()
{
    TMessage*   m   = message->getItem();
    TMessage    toHandle;
    toHandle.type = m->type;
    delete m;
    if (m == 0)
    {
        toHandle.type = MSG_NULL;
    }
    end = clock();
    if ((end - start) / CLK_TCK * 1000 >= interval)
    {
        if (enabled)
        {
            TMessage    tm;
            tm.type = MSG_TIMER;
            addMessage(&tm);
        }
        start = clock();
        end = start;
    }
    if (toHandle.type == MSG_TIMER)
    {
        if (onTimer != 0)
        {
            onTimer(this, 0);
        }
    }
}