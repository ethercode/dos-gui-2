#ifndef _BUTTON_
#define _BUTTON_

#include "object.h"

class TButton:public TObject
{
public:
            TButton();
            ~TButton();
    void    handler();
    void    setCaption(char*);
    char*   getCaption(void);
    void    setFlat(int);
    void    drawFocusBlock();
private:
    int     flat;
    int     isDown;
    char    caption[60];
    int     standardColour[4];
    int     fontType, fontColour, fontSize;
    void    flatPaint();
    void    downPaint();
    void    upPaint();
};

#endif