/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: declaration of arg.  Arg holds any amount of parameters to be used
          in a stack or recursion function.
*/
#include "stackLink.h"
#include "stack.h"
#include "rule.h"
#include "ASTNode.h"
#include <type_traits>

#ifndef ARG_H
#define ARG_H

class arg {
    //  Arg class holds any amount of items as parameters.
public:
    arg();
    template <typename... Args>
    arg(Args... args);
    void *get(int i);
    int getSize();
    stack *values;
    arg *copy();
    ~arg();

protected:
    stackLink *link;
    int size = 0;
    template <typename T, typename... Args>
    void populate(stackLink *current, T par, Args... Arg);
    template <typename T>
    void populate(stackLink *current, T par);
    void checkRule(stackLink *add, rule *par);
    void checkRule(stackLink *add, void *par);
};

//  Can pass any number of items into arg.
template <typename... Args>
arg::arg(Args... args) {
    size = 0;
    link = new stackLink();
    link->test = "init";
    populate(link, args...);
}

//  Parametric recursion to build linked list of arguments.
template <typename T, typename... Args>
void arg::populate(stackLink *current, T par, Args... Arg) {
    stackLink *add = new stackLink();
    add->test = "append";
    add->hasItem = true;
    checkRule(add, par);

    if (size == 0) {
        size++;
        *current = *add;
        populate(current, Arg...);
    } else {
        size++;
        current->link = add;
        populate(current->link, Arg...);
    }
};

//  Base case of parametric recursion for arg population.
template <typename T>
void arg::populate(stackLink *current, T par) {
    stackLink *add = new stackLink();
    add->test = "append";
    add->item = par;
    add->hasItem = true;
    checkRule(add, par);

    if (size == 0) {
        *current = *add;
    } else {
        current->link = add;
    }
    size++;
};

#endif