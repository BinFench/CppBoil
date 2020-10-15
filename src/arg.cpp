#include "arg.h"

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
    return nullptr;
}