#ifndef _COLOURSCHEME_
#define _COLOURSCHEME_

#include "compattr.h"

const   SCHEME_STANDARD = 0;
const   SCHEME_SKY      = 1;

class TColourScheme
{
public:
                TColourScheme::TColourScheme();
    TCompAttr*  getCompAttr();
    void        setCompAttr(TCompAttr*);
    void        setPredefined(int num);
    void        applyScheme(void);
private:
    int         constructing;
    TCompAttr   compAttr;
};

#endif