/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: implementation of stack defined in stack.h.  Stack holds the tokenized
          items from parsing a source string.
*/
#include "stack.h"

stack::stack() {
    size = 0;
}

//  Push item onto stack, flag if the item is a rule or not.
void stack::push(void *item) {
    stackLink *link = new stackLink();
    link->test = "stack";
    link->item = item;
    link->isRule = false;
    link->hasItem = true;
    if (size == 0) {
        head = link;
    } else {
        link->link = head;
        head = link;
    }

    size++;
}

//  Push item onto stack, flag if the item is a rule or not.
void stack::push(rule *item) {
    stackLink *link = new stackLink();
    link->test = "stack";
    link->item = item;
    link->isRule = true;
    link->hasItem = true;
    if (size == 0) {
        head = link;
    } else {
        link->link = head;
        head = link;
    }

    size++;
}

//  Pop item from top of stack.
void *stack::pop() {
    if (size > 0) {
        stackLink *link = head;
        head = head->link;
        void *item = link->item;
        delete link;
        size--;
        return item;
    }
    return nullptr;
}

//  Swap item from top of stack with item below.
void stack::swap() {
    if (size >= 2) {
        stackLink *link1 = head;
        stackLink *link2 = head->link;
        link1->link = link2->link;
        link2->link = link1;
        head = link2;
    }
}

//  Get reference to item at top of stack.
void *stack::peek() {
    if (size > 0) {
        return head->item;
    }
    return nullptr;
}

int stack::getSize() {
    return size;
}

//  Destructor: deletes nodes in stack, items are the user's responsibility.
stack::~stack() {
    if (size > 0) {
        stackLink *current = head;
        stackLink *toDel = head;

        for (int i = 0; i < size - 1; i++) {
            current = current->link;
            delete toDel;
            toDel = current;
        }
        delete toDel;
    }
}