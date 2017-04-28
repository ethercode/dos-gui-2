#ifndef _TDESKTOP_
#define _TDESKTOP_

#include "object.h"

class TDesktop:public TObject
{
public:
            TDesktop();
            ~TDesktop();
    void    handler(void);
private:
    void    standardPaint(void);
    int     colour;
};

#endif