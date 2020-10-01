#include "linkNode.h"

linkNode::linkNode() {
    hasChild = false;
    hasSibling = false;
}

void linkNode::append(linkNode* sibling) {
    hasSibling = true;
    sibling = sibling;
}

void linkNode::attach(ASTNode* child) {
    hasChild = true;
    ASTChildren = child;
}