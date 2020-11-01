/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: declaration of stack.  Stack holds the tokenized
          items from parsing a source string.
*/
#include "stackLink.h"
#include "../parser/rule.h"

#ifndef STACK_H
#define STACK_H

class stack {
    //  Container for tokenized items.
public:
    stack();
    void push(void *item);
    void push(rule *item);
    void *pop();
    void swap();
    void *peek();
    int getSize();
    ~stack();

protected:
    int size;
    stackLink *head;
};

#endif