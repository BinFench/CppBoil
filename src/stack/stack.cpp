#include "stack.h"
#include <iostream>

stack::stack()
{
    size = 0;
}

void stack::push(void *item)
{
    std::cout << "push item!" << std::endl;
    std::cout << *(static_cast<std::string *>(item)) << std::endl;
    stackLink *link = new stackLink();
    link->test = "stack";
    link->item = item;
    link->isRule = false;
    link->hasItem = true;
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

void stack::push(rule *item)
{
    std::cout << "push rule!" << std::endl;
    stackLink *link = new stackLink();
    link->test = "stack";
    link->item = item;
    link->isRule = true;
    link->hasItem = true;
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
    std::cout << "pop!" << std::endl;
    if (size > 0)
    {
        stackLink *link = head;
        head = head->link;
        void *item = link->item;
        delete link;
        size--;
        return item;
    }
    std::cout << "Stack empty" << std::endl;
    return nullptr;
}

void stack::swap()
{
    std::cout << "swap!" << std::endl;
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
    std::cout << "peek!" << std::endl;
    if (size > 0)
    {
        return head->item;
    }
    return nullptr;
}