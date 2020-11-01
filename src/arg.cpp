/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: implementation of arg defined in arg.h.  Arg holds any amount of
          parameters to be used in a stack or recursion function.
*/
#include "arg.h"

arg::arg() {
    size = 0;
}

int arg::getSize() {
    return size;
}

void *arg::get(int i) {
    if (i < size) {
        return link->get(i, values);
    }
    return nullptr;
}

//  Utility function, to assign rule or item to stackLink
void arg::checkRule(stackLink *add, rule *par) {
    add->isRule = true;
    add->item = par->copy();
    delete par;
}

//  Utility function, to assign rule or item to stackLink
void arg::checkRule(stackLink *add, void *par) {
    add->isRule = false;
    add->item = par;
}

//  Copy function for memory management.
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

//  Destructor: cleans up stackLinks.  User handles items held in arg.
arg::~arg() {
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