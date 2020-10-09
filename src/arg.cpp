#include "arg.h"
#include "stack/stackLink.h"
#include "parser/rule.h"
#include "ast/ASTNode.h"
#include <type_traits>

int arg::getSize()
{
    return size;
}

void *arg::get(int i)
{
    if (i <= size)
    {
        stackLink *current = link;
        for (int j = 0; j < i; j++)
        {
            current = current->link;
        }

        void *toRet = current->item;
        if (current->isRule && (((rule *)(current->item))->getNode()->getId() == "pop" || ((rule *)(current->item))->getNode()->getId() == "peek"))
        {
            toRet = ((rule *)(current->item))->getNode()->act(values);
        }

        return toRet;
    }
}

template <typename... Args>
arg::arg(Args... args)
{
    size = 0;
    populate(link, args...);
}

template <typename T, typename... Args>
void arg::populate(stackLink *current, T par, Args... Arg)
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

    populate(add, Arg...);
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
};