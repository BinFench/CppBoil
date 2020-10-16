#ifndef STACKLINK_H
#define STACKLINK_H

class stackLink {
    public:
        stackLink *link;
        bool isRule;
        void *item;

        stackLink();
};

#endif