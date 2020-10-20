#include "arg.h"
#include <iostream>

int arg::getSize()
{
    return size;
}

void *arg::get(int i)
{
    std::cout << link->test << std::endl;
    if (i < size)
    {
        stackLink *current = link;
        for (int j = 0; j < i; j++)
        {
            std::cout << j << std::endl;
            current = current->link;
        }

        void *toRet;
        std::cout << current->isRule << std::endl;
        std::cout << current->hasItem << std::endl;
        std::cout <<"Here is where it crashes now" << std::endl;
        std::cout << current->test << std::endl;
        if (current->isRule && current->hasItem && (((rule *)(current->item))->getNode()->getId() == "pop" || ((rule *)(current->item))->getNode()->getId() == "peek"))
        {
            std::cout << "This happens I swear" << std::endl;
            toRet = static_cast<void*>(((rule *)(current->item))->getNode()->act(values));
        } else if (current->hasItem) {
            toRet = static_cast<void*>(current->item);
        } else {
            toRet = nullptr;
        }

        std::cout << "arg success" << std::endl;
        return toRet;
    }
    std::cout << "arg fail" << std::endl;
    return nullptr;
}

void arg::checkRule (stackLink *add, rule *par) {
    std::cout << "rule found" << std::endl;
    add->isRule = true;
}

void arg::checkRule (stackLink *add, void *par) {
    std::cout << "nonrule found" << std::endl;
    add->isRule = false;
}