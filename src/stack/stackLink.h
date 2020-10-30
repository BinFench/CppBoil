#include <string>

#ifndef STACKLINK_H
#define STACKLINK_H

class stack;

class stackLink {
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