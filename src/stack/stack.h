#include "stackLink.h"

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