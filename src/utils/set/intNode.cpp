#include "intNode.h"

void intNode::attach(int ch) {
    hasChild = true;
    child = ch;
}

int intNode::getChild() {
    if (hasChild) {
        return child;
    }
    return -1;
}

void intNode::increment() {
    child++;
}