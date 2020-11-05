/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: declaration of arg.  Arg holds any amount of parameters to be used
          in a stack or recursion function.
*/
#include "stack/stackLink.h"
#include "stack/stack.h"
#include "parser/rule.h"
#include "ast/ASTNode.h"
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
    current->test = "append";
    current->hasItem = true;
    checkRule(current, par);
    size++;
    current->link = new stackLink();
    populate(current->link, Arg...);
};

//  Base case of parametric recursion for arg population.
template <typename T>
void arg::populate(stackLink *current, T par) {
    current->test = "append";
    current->item = par;
    current->hasItem = true;
    checkRule(current, par);
    size++;
};

#endif