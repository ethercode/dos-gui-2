#include "mstack.h"

TStack::TStack()
{
    first = 0;
}

TStack::~TStack()
{
    TStackItem* temp    = first;
    TStackItem* temp2;
    while (temp != 0)
    {
        temp2 = first->next;
        delete temp->message;
        temp->message = 0;
        delete temp;
        temp = temp2;
        first = temp;
    }
}

TMessage* TStack::getItem()
{
    if (first == 0)
    {
        return 0;
    }
    TMessage*   mes = first->message;
    TStackItem* st  = first->next;
    delete first;
    first = st;
    return mes;
}

void TStack::addMessage(TMessage* newMessage)
{
    if (first == 0)
    {
        first = new TStackItem;
        first->message = newMessage;
        first->next = 0;
        last = first;
    }
    else
    {
        last->next = new TStackItem;
        last->next->next = 0;
        last = last->next;
        last->message = newMessage;
    }
}
