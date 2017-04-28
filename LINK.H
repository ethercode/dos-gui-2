#ifndef _LINK_
#define _LINK_

class   TObject;

class TLink
{
public:
            TLink();
            ~TLink();
    TLink*  next;
    TObject*object;
};

#endif
