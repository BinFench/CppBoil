#ifndef STACKLINK_H
#define STACKLINK_H

class stackLink {
    public:
        stackLink *link;
        void *item;

        stackLink();
};

#endif