#include "stackLink.h"
#include "../parser/rule.h"
#include <iostream>

stackLink::stackLink() {
    isRule = false;
    hasItem = false;
    test = "neither";
}

stackLink *stackLink::copy() {
    stackLink *newLink = new stackLink();
    newLink->isRule = isRule;
    newLink->hasItem = hasItem;

    if (isRule) {
        newLink->item = ((rule *)item)->copy();
    } else if (hasItem) {
        newLink->item = item;
    }

    return newLink;
}

stackLink::~stackLink() {
    std::cout << "stackLink" << std::endl;
    std::cout << isRule << std::endl;
    if (isRule) {
        std::cout << "rule" << std::endl;
        delete ((rule *)item);
    }
    std::cout << "Deleted" << std::endl;
}