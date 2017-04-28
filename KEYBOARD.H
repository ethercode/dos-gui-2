#ifndef _TKeyboard_
#define _TKeyboard_

#include "object.h"

class TKeyboard:public TObject
{
public:
            TKeyboard();
            ~TKeyboard();
    void    handler(void);
    TObject*getFocused();
    void    setFocused(TObject*);
    void    focusNext();
    void    focusPrev();
private:
    TObject*focused;
};

#endif