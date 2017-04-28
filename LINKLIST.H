#ifndef _LINKLIST_
#define _LINKLIST_

#include "link.h"

class TLinkedList
{
public:
            TLinkedList();
            ~TLinkedList();
    void    addItem(TObject* source);
    void    deleteItem(TObject* item);
    void    unlistItem(TObject* item);
    int     where(TObject*);
    int     total();
    TObject*get(int);
private:
    TLink*  head;
};

#endif
