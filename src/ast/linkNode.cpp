#include "linkNode.h"
#include "ASTNode.h"
#include <iostream>

linkNode::linkNode() {
    hasChild = false;
    hasSibling = false;
}

void linkNode::append(linkNode *nsibling) {
    hasSibling = true;
    sibling = nsibling;
}

void linkNode::attach(ASTNode *child) {
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

void linkNode::removeTail() {
    if (hasSibling) {
        linkNode *current = getSibling();
        linkNode *prev = this;
        while (current->hasSibling) {
            prev = current;
            current = current->getSibling();
        }
        prev->hasSibling = false;
        if (current->hasChild) {
            delete current->ASTChildren;
        }
        delete current;
    }
}

linkNode *linkNode::copy() {
    linkNode *toRet = new linkNode();
    if (hasChild) {
        toRet->ASTChildren = ASTChildren->copy();
    }
    if (hasSibling) {
        toRet->sibling = sibling->copy();
    }

    return toRet;
}

linkNode::~linkNode() {
    std::cout << "link" << std::endl;
    if (hasChild) {
        std::cout << "link children" << std::endl;
        delete ASTChildren;
    }
    if (hasSibling) {
        std::cout << "link sibling" << std::endl;
        delete sibling;
    }
}