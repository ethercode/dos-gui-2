#ifndef _MESSAGE_
#define _MESSAGE_

class TMessage
{
public:
                    TMessage();
                    ~TMessage();
    int             type;
    unsigned char   keyPress[2];
};

#endif

#ifndef _MSG_CONST_
#define _MSG_CONST_

const           MSG_NULL                = 0;
const           MSG_PAINT               = 1;
const           MSG_MOUSE_ENTER         = 2;
const           MSG_MOUSE_LEAVE         = 3;
const           MSG_MOUSE_LEFT_DOWN     = 4;
const           MSG_MOUSE_LEFT_UP       = 5;
const           MSG_MOUSE_LEFT_CLICK    = 6;
const           MSG_UPDATECOLOURS       = 7;
const           MSG_FOCUS_LOST          = 8;
const           MSG_FOCUS_GAINED        = 9;
const           MSG_KEYPRESS            = 10;
const           MSG_TIMER               = 11;

#endif