#include <string>

#ifndef STACKLINK_H
#define STACKLINK_H

class stackLink {
    public:
        stackLink *link;
        bool isRule;
        void *item;
        bool hasItem;
        std::string test;
        stackLink *copy();

        stackLink();
        ~stackLink();
};

#endif