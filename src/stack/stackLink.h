/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: definition of stackLink.  StackLinks are
          used to hold the items and build the stack.
*/
#include <string>

#ifndef STACKLINK_H
#define STACKLINK_H

//  Forward declaration, see stack.h
class stack;

class stackLink {
    //  The links that build stack and arg objects.
    public:
        stackLink *link;
        bool isRule;
        void *item;
        bool hasItem;
        std::string test;
        stackLink *copy();
        void *get(int i, stack *values);

        stackLink();
        ~stackLink();
};

#endif