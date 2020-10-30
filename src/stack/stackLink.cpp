#include "stackLink.h"
#include "../parser/rule.h"
#include "../ast/ASTNode.h"
#include <iostream>

stackLink::stackLink() {
    isRule = false;
    hasItem = false;
    test = "neither";
    std::cout << "create: " << isRule << std::endl;
}

stackLink *stackLink::copy() {
    stackLink *newLink = new stackLink();
    newLink->isRule = isRule;
    std::cout << "copy: " << isRule << std::endl;
    newLink->hasItem = hasItem;
    newLink->test = "copy";

    if (isRule) {
        newLink->item = ((rule *)item)->copy();
    } else if (hasItem) {
        newLink->item = item;
    }

    return newLink;
}

void *stackLink::get(int i, stack *values) {
    if (i > 0) {
        return link->get(i-1, values);
    }
    void *toRet;
    if (isRule && (((rule *)(item))->getNode()->getId() == "pop" || ((rule *)(item))->getNode()->getId() == "peek")) {
        toRet = static_cast<void *>(((rule *)(item))->getNode()->act(values));
    } else if (hasItem) {
        toRet = static_cast<void *>(item);
    } else {
        toRet = nullptr;
    }
    return toRet;
}

stackLink::~stackLink() {
    std::cout << "stackLink" << std::endl;
    std::cout << isRule << std::endl;
    if (isRule) {
        delete ((rule *)item);
    }
    std::cout << "Deleted" << std::endl;
}