#include "arg.h"
#include <iostream>

arg::arg() {
    size = 0;
}

int arg::getSize() {
    return size;
}

void *arg::get(int i) {
    if (i < size) {
        stackLink *current = link;
        for (int j = 0; j < i; j++) {
            current = current->link;
        }

        void *toRet;
        if (current->isRule && (((rule *)(current->item))->getNode()->getId() == "pop" || ((rule *)(current->item))->getNode()->getId() == "peek")) {
            toRet = static_cast<void *>(((rule *)(current->item))->getNode()->act(values));
        } else if (current->hasItem) {
            toRet = static_cast<void *>(current->item);
        } else {
            toRet = nullptr;
        }

        return toRet;
    }
    return nullptr;
}

void arg::checkRule(stackLink *add, rule *par) {
    add->isRule = true;
}

void arg::checkRule(stackLink *add, void *par) {
    add->isRule = false;
}

arg *arg::copy() {
    arg *newArg = new arg();
    if (size > 0) {
        newArg->link = link->copy();
        stackLink *current;
        stackLink *newCurr;
        newCurr = newArg->link;
        current = link;
        newArg->size++;
        for (int i = 0; i < size - 1; i++) {
            newCurr->link = current->link->copy();
            newCurr = newCurr->link;
            current = current->link;
            newArg->size++;
        }
    }
    return newArg;
}

arg::~arg() {
    std::cout << "Cleaning up args: " << size << std::endl;
    if (size > 0) {
        stackLink *current = link;
        stackLink *toDel = link;

        for (int i = 0; i < size - 1; i++) {
            std::cout << "Loop" << std::endl;
            current = current->link;
            delete toDel;
            toDel = current;
        }
        std::cout << "Oop" << std::endl;
        delete toDel;
    }
    std::cout << "Cleaned" << std::endl;
}