#ifndef _OBJECT_
#define _OBJECT_

#include "fpointer.h"
#include "standard.h"
#include "linklist.h"
#include "mstack.h"
#include "message.h"
#include "event.h"
#include "cursor.h"

class TObject
{
public:
                    TObject();
                    ~TObject();
    virtual void    handler(void);
    void            handleChildren(void);
    void            activate(void);
    void            deactivate(void);
    void            addChild(TObject*);
    void            deleteChild(TObject*);
    void            changeContainer(TObject*);
    void            sendMessage(TObject*, TMessage*);
    void            treeSendMessage(TObject*, TMessage*, int);
    void            globalSendMessage(TMessage*);
    void            addMessage(TMessage*);
    void            paint(void);
    int             whichChild(TObject*);
    TPoint*         getLocation();
    TPoint*         getSize();
    void            setLocation(TPoint*);
    void            setSize(TPoint*);
    int             totalChildren();
    TObject*        getChild(int);
    int             getAbsoluteX();
    int             getAbsoluteY();
    TObject*        getContainer();
    TEvent          onClick, onLeftUp, onLeftDown;
    TEvent          onKeyPress;
    TEvent          onPaint, onLeave, onEnter;
    TEvent          onActivate;
    int             mayFocus();
    void            setFocusable(int);
    int             isActive();
    int             isFocused();
    void            focus();
    void            showMyCursor();
protected:
    TCursor*        cursor;
    int             standardShade[4];
    int             fontColour, fontType, fontSize;
    int             focusable;
    FP_VOID_VOID    paintFunc;
    TPoint          location;
    TPoint          size;
    int             isGraphical;
    void            removeChild(TObject*);
    TObject*        container;
    TLinkedList*    child;
    TStack*         message;
    int             active;
    int             mouseState;
};

#endif