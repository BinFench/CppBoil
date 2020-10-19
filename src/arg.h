#include "stack/stackLink.h"
#include "stack/stack.h"
#include "stack/stackLink.h"
#include "parser/rule.h"
#include "ast/ASTNode.h"
#include <type_traits>

#ifndef ARG_H
#define ARG_H

class arg
{
public:
    template <typename... Args>
    arg(Args... args);
    void *get(int i);
    int getSize();
    stack *values;

protected:
    stackLink *link;
    int size;
    template <typename T, typename... Args>
    void populate(stackLink *current, T par, Args... Arg);
    template <typename T>
    void populate(stackLink *current, T par);
};

template <typename... Args>
arg::arg(Args... args)
{
    size = 0;
    link = new stackLink();
    populate(link, args...);
}

template <typename T, typename... Args>
void arg::populate(stackLink *current, T par, Args... Arg)
{
    stackLink *add = new stackLink();
    add->item = par;
    add->hasItem = true;

    if (std::is_same<T, rule*>::value)
    {
        add->isRule = true;
    }

    if (size == 0)
    {
        size++;
        delete current;
        current = add;
        populate(current, Arg...);
    }
    else
    {
        size++;
        current->link = add;
        populate(current->link, Arg...);
    }
};

template <typename T>
void arg::populate(stackLink *current, T par)
{
    stackLink *add = new stackLink();
    add->item = par;

    if (std::is_same<T, rule>::value)
    {
        add->isRule = true;
    }

    if (size == 0)
    {
        current = add;
    }
    else
    {
        current->link = add;
    }
    size++;
};

#endif