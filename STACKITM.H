#ifndef _STACKITEM_
#define _STACKITEM_

#include "message.h"

struct TStackItem
{
    TMessage*   message;
    TStackItem* next;
};

#endif
