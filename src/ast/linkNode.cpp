#include "linkNode.h"
#include "ASTNode.h"
#include <iostream>

linkNode::linkNode()
{
    hasChild = false;
    hasSibling = false;
}

void linkNode::append(linkNode *nsibling)
{
    hasSibling = true;
    sibling = nsibling;
}

void linkNode::attach(ASTNode *child)
{
    hasChild = true;
    ASTChildren = child;
}

ASTNode *linkNode::getChild()
{
    return ASTChildren;
}

linkNode *linkNode::getSibling()
{
    return sibling;
}

linkNode *linkNode::getTail()
{
    if (hasSibling)
    {
        linkNode *current = getSibling();
        while (current->hasSibling)
        {
            current = current->getSibling();
        }
        return current;
    }
    return this;
}

void linkNode::print() {
    std::cout << "In link" << std::endl;
    if (hasChild) {
        std::cout << ASTChildren->getId() << std::endl;
    }
    if (hasSibling) {
        sibling->print();
    }
}

void linkNode::removeTail() {
    if (hasSibling)
    {
        linkNode *current = getSibling();
        linkNode *prev = this;
        while (current->hasSibling)
        {
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