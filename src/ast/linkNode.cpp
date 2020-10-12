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

ASTNode *linkNode::getChild() {
    return ASTChildren;
}

linkNode *linkNode::getSibling() {
    return sibling;
}

linkNode *linkNode::getTail() {
    if (hasSibling) {
        linkNode *current = getSibling();
        while (current->hasSibling) {
            current = current->getSibling();
        }
        return current;
    }
    return this;
}