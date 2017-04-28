#ifndef _TFORM_
#define _TFORM_

#include "object.h"

class TPanel:public TObject
{
public:
            TPanel();
            ~TPanel();
    void    handler();
protected:
    int     standardColour[4];
    void    standardPaint(void);
};

#endif