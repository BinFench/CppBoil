#include "arg.h"
#include <iostream>

int arg::getSize()
{
    return size;
}

void *arg::get(int i)
{
    if (i < size)
    {
        stackLink *current = link;
        for (int j = 0; j < i; j++)
        {
            current = current->link;
        }

        void *toRet;
        if (current->isRule && current->hasItem && (((rule *)(current->item))->getNode()->getId() == "pop" || ((rule *)(current->item))->getNode()->getId() == "peek"))
        {
            std::cout << "This happens" << std::endl;
            toRet = static_cast<void *>(((rule *)(current->item))->getNode()->act(values));
        }
        else if (current->hasItem)
        {
            toRet = static_cast<void *>(current->item);
        }
        else
        {
            toRet = nullptr;
        }

        return toRet;
    }
    return nullptr;
}

void arg::checkRule(stackLink *add, rule *par)
{
    add->isRule = true;
}

void arg::checkRule(stackLink *add, void *par)
{
    add->isRule = false;
}