#ifndef _CURSOR_
#define _CURSOR_

const   CSR_STANDARD    = 0;
const   CSR_MOVEMENT    = 1;
const   CSR_DISABLED    = 2;
const   CSR_EZGUI       = 3;

class TCursor
{
public:
                TCursor(char*, int, int);
    void        show();
private:
    int         hx, hy;
    unsigned    data[32];
};

#endif
