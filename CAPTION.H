#ifndef _CAPTION_
#define _CAPTIOM_

#include "object.h"
#include "button.h"

class TCaption:public TObject
{
public:
            TCaption();
            ~TCaption();
    void    setCaption(char*);
    char*   getCaption();
    void    handler();
private:
    void    standardPaint(void);
    char    caption[60];
    int     capLeftCol, capRightCol;
    int     fontType, fontColour, fontSize;
    TButton*closeButton;
};

#endif