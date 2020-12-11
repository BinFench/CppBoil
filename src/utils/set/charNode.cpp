#include "charNode.h"

void charNode::attach(char ch) {
    hasChild = true;
    child = ch;
}

char charNode::getChild() {
    if (hasChild) {
        return child;
    }
    return '\0';
}