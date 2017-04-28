#ifndef _MSTACK_
#define _MSTACK_

#include "stackitm.h"

class TStack
{
public:
                TStack();
                ~TStack();
    TMessage*   getItem();
    void        addMessage(TMessage*);
private:
    TStackItem* first;
    TStackItem* last;
};

#endif
