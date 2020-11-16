/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: declaration of linked list nodes.
          linkNodes store the children of ASTNodes, as well as a linked list
          of stack actions for post parse processing.
*/

//Forward declaration, see ASTNode.h
class ASTNode;

#ifndef LINKNODE_H
#define LINKNODE_H

class linkNode {
    //  Node for linked list.
public:
    linkNode();
    void append(linkNode *sibling);
    void attach(ASTNode *child);
    bool hasSibling;
    bool hasChild;
    bool isSimplified;
    void removeTail();
    linkNode *copy();
    ~linkNode();

    ASTNode *getChild();
    linkNode *getSibling();
    linkNode *getTail();

protected:
    ASTNode *ASTChildren;
    linkNode *sibling;
};

#endif