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
        toRet->attach(ASTChildren->copy());
    }
    if (hasSibling) {
        toRet->append(sibling->copy());
    }
    toRet->isSimplified = isSimplified;

    return toRet;
}

void linkNode::simplify(bool *simplified) {
    if (!isSimplified) {
        ASTNode *simple = ASTChildren->simplify(simplified);
        delete ASTChildren;
        ASTChildren = simple;
        if (*simplified) {
            isSimplified = true;
        }
    } else {
        *simplified = true;
    }
}

linkNode *linkNode::mergeSequenceGrandchildren(bool *simplified) {
    //  If any child node is sequence, add the children to this linked list
    //  Else, simplify
    if (hasChild) {
        bool *temp = new bool();
        *temp = false;
        if (ASTChildren->getId() == "sequence") {
            linkNode *toRet = ASTChildren->getChildren()->copy();
            if (hasSibling) {
                if (!sibling->isSimplified) {
                    sibling = sibling->mergeSequenceGrandchildren(temp);
                }
                toRet->getTail()->append(sibling->copy());
            }
            delete temp;
            return toRet;
        } else if (ASTChildren->getId() == "firstOf") {
            //  Transform child to be subrule
            ASTChildren = new ruleNode(ASTChildren);
            if (hasSibling && !sibling->isSimplified) {
                sibling = sibling->mergeSequenceGrandchildren(temp);
            } else {
                *temp = true;
            }
            simplify(simplified);
            *simplified = *temp && *simplified;
            delete temp;
            return copy();
        } else {
            if (hasSibling && !sibling->isSimplified) {
                sibling = sibling->mergeSequenceGrandchildren(temp);
            } else {
                *temp = true;
            }
            simplify(simplified);
            *simplified = *temp && *simplified;
            delete temp;
            return copy();
        }
    }
    if (hasSibling && !sibling->isSimplified) {
        sibling = sibling->mergeSequenceGrandchildren(simplified);
        return sibling->copy();
    }
    *simplified = true;
    return copy();
}

linkNode::~linkNode() {
    if (hasChild) {
        delete ASTChildren;
    }
    if (hasSibling) {
        delete sibling;
    }
}