#include "stack/stackLink.h"
#include "stack/stack.h"

#ifndef ARG_H
#define ARG_H

class arg {
    public:
        template<typename... Args>
        arg(Args... args);
        void *get(int i);
        int getSize();
        stack *values;

    protected:
        stackLink *link;
        int size;
        template<typename T, typename... Args>
        void populate(stackLink *current, T par, Args... Arg);
        template<typename T>
        void populate(stackLink *current, T par);
};

#endif