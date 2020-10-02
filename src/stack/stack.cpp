#include "stack.h"

stack::stack()
{
    size = 0;
}

void stack::push(void *item)
{
    stackLink *link = new stackLink();
    link->item = item;
    if (size == 0)
    {
        head = link;
    }
    else
    {
        link->link = head;
        head = link;
    }

    size++;
}

void *stack::pop()
{
    if (size > 0)
    {
        stackLink *link = head;
        head = head->link;
        void *item = link->item;
        delete link;
        size--;
        return item;
    }
}

void stack::swap()
{
    if (size > 2)
    {
        stackLink *link1 = head;
        stackLink *link2 = head->link;
        link1->link = link2->link;
        link2->link = link1;
        head = link2;
    }
}

void *stack::peek()
{
    if (size > 0)
    {
        return head->item;
    }
}