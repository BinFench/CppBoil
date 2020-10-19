#include "arg.h"
#include <iostream>

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
            std::cout << j << std::endl;
            current = current->link;
        }

        void *toRet;
        toRet = static_cast<void*>(current->item);
        std::cout << current->isRule << std::endl;
        if (current->isRule && (((rule *)(current->item))->getNode()->getId() == "pop" || ((rule *)(current->item))->getNode()->getId() == "peek"))
        {
            std::cout << "This happens I swear" << std::endl;
            toRet = static_cast<void*>(((rule *)(current->item))->getNode()->act(values));
        }

        std::cout << "arg success" << std::endl;
        return toRet;
    }
    std::cout << "arg fail" << std::endl;
    return nullptr;
}