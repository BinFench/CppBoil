/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: implementation of linked list nodes defined in linkNode.h
          linkNodes store the children of ASTNodes, as well as a linked list
          of stack actions for post parse processing.
*/
#include "linkNode.h"
#include "ASTNode.h"

linkNode::linkNode() {
    hasChild = false;
    hasSibling = false;
    isSimplified = false;
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

//  Get very end of linked list.
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

//  Remove last node in linked list.
void linkNode::removeTail() {
    if (hasSibling) {
        linkNode *current = getSibling();
        linkNode *prev = this;
        while (current->hasSibling) {
            prev = current;
            current = current->getSibling();
        }
        prev->hasSibling = false;
        delete current;
    }
}

//  Copy entire linked list from this node to tail.
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
    if (hasChild) {
        delete ASTChildren;
    }
    if (hasSibling) {
        delete sibling;
    }
}