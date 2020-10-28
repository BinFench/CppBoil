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
        if (current->isRule && current->hasItem && (((rule *)(current->item))->getNode()->getId() == "pop" || ((rule *)(current->item))->getNode()->getId() == "peek")) {
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

void *arg::copy(int i) {
    if (i < size) {
        stackLink *current = link;
        for (int j = 0; j < i; j++) {
            current = current->link;
        }

        void *toRet;
        if (current->isRule && current->hasItem) {
            toRet = static_cast<void *>(new rule(((rule *)(current->item))->getNode()->copy()));
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

void arg::add(void *toAdd, bool Rule) {
    if (size == 0) {
        link = new stackLink();
        link->isRule = Rule;
        link->item = toAdd;
    } else {
        stackLink *current = link;
        for (int i = 0; i < size - 1; i++) {
            current = current->link;
        }
        current->link = new stackLink();
        current = current->link;
        current->isRule = Rule;
        current->item = toAdd;
    }

    size++;
}

bool arg::isRule(int i) {
    if (i < size) {
        stackLink *current = link;
        for (int j = 0; j < i; j++) {
            current = current->link;
        }
        return current->isRule;
    }
    return false;
}

arg::~arg() {
    std::cout << "arg" << std::endl;
    if (size > 0) {
        stackLink *current = link;
        stackLink *toDel = link;

        for (int i = 0; i < size - 1; i++) {
            current = current->link;
            delete toDel;
            toDel = current;
        }
        delete toDel;
    }
}