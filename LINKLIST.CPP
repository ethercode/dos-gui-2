#include "linklist.h"
#include "link.h"
#include "object.h"

TLinkedList::TLinkedList()
{
    head = 0;
}

TLinkedList::~TLinkedList()
{
    TLink*  temp    = head;
    TLink*  temp2;
    while (temp != 0)
    {
        temp2 = temp->next;
        delete temp->object;
        temp->object = 0;
        delete temp;
        temp = temp2;
    }
}

void TLinkedList::addItem(TObject* source)
{
    TLink*  current = head;

    if (head == 0)
    {
        head = new TLink;
        head->object = source;
        head->next = 0;
    }
    else if (head->next == 0)
    {
        head->next = new TLink;
        head->next->object = source;
        head->next->next = 0;
    }
    else
    {
        while (current->next != 0)
        {
            current = current->next;
        }
        current->next = new TLink;
        current = current->next;
        current->object = source;
        current->next = 0;
    }
}

void TLinkedList::deleteItem(TObject* item)
{
    if (head->object == item)
    {
        TLink*  temp    = head->next;
        delete head->object;
        head->object = 0;
        delete head;
        head = temp;
    }
    else
    {
        TLink*  current = head;
        while (current->next->object != item)
        {
            if (current == 0)
            {
                return;
            }
            current = current->next;
        }
        TLink*  temp    = current->next->next;
        delete current->next->object;
        current->object = 0;
        delete current->next;
        current->next = temp;
    }
}

void TLinkedList::unlistItem(TObject* item)
{
    if (head->object == item)
    {
        TLink*  temp    = head->next;
        delete head;
        head = temp;
    }
    else
    {
        TLink*  current = head;
        while (current->next->object != item)
        {
            if (current == 0)
            {
                return;
            }
            current = current->next;
        }
        TLink*  temp    = current->next->next;
        delete current->next;
        current->next = temp;
    }
}

int TLinkedList::total()
{
    if (head == 0)
    {
        return 0;
    }
    if (head->next == 0)
    {
        return 1;
    }
    TLink*  obj = head;
    int     tot = 1;
    while (obj->next != 0)
    {
        tot++;
        obj = obj->next;
    }
    return tot;
}

int TLinkedList::where(TObject* obj)
{
    int a   = total();

    if (a == 0)
    {
        return -1;
    }
    int     b       = 0;
    TLink*  temp    = head;
    while (b < a)
    {
        if (temp->object == obj)
        {
            return b;
        }
        temp = temp->next;
        b++;
    }
    return -2;
}

TObject* TLinkedList::get(int index)
{
    int     x;
    TLink*  link    = head->next;
    if (index == 0)
    {
        if (head == 0)
        {
            return 0;
        }
        return head->object;
    }
    for (x = 0; x < index - 1; x++)
    {
        if (link->next == 0)
        {
            return 0;
        }
        link = link->next;
    }
    if (link == 0)
    {
        return 0;
    }
    return link->object;
}

