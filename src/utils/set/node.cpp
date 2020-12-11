#include "node.h"

void node::append(node *sib) {
    if (hasSibling) {
        sibling->append(sib);
    } else {
        hasSibling = true;
        sibling = sib;
    }
}

node *node::getSibling() {
    if (hasSibling) {
        return sibling;
    }
    return nullptr;
}

node::~node() {
    if (hasSibling) {
        delete getSibling();
    }
}