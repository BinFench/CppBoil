#include "stackLink.h"

#ifndef STACK_H
#define STACK_H

class stack
{
public:
    stack();
    void push(void *item);
    void *pop();
    void swap();
    void *peek();

protected:
    int size;
    stackLink *head;
};

#endif