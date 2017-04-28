#ifndef _GUI_
#define _GUI_

#include "mouse.h"
#include "object.h"
#include "cscheme.h"
#include "keyboard.h"
#include "cursor.h"

class TGui
{
public:
                    TGui();
                    ~TGui();
    void            stopGui();
    void            execute();
    void            init();
    void            loop();
    void            exit();
    void            hideMouse(void);
    void            showMouse(void);
    void            setGraphics();
    void            setText();
    TObject*        getDesktop(void);
    TMouse*         getMouse(void);
    TKeyboard*      getKeyboard(void);
    TColourScheme   colourScheme;
    void            allowPainting();
    void            disallowPainting();
    int             mayIPaint();
    TCursor*        getCursor(int);
private:
    int             canPaint;
    int             mustExit;
    int             graphicsOn;
    TObject*        desktop;
    TKeyboard*      keyboard;
    TMouse*         mouse;
};

#endif
