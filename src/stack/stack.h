#include "stackLink.h"
#include "../parser/rule.h"

#ifndef STACK_H
#define STACK_H

class stack
{
public:
    stack();
    void push(void *item);
    void push(rule *item);
    void *pop();
    void swap();
    void *peek();
    int getSize();

protected:
    int size;
    stackLink *head;
};

#endif