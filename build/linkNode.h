class ASTNode;

#ifndef LINKNODE_H
#define LINKNODE_H

class linkNode {
    public:
        linkNode();
        void append(linkNode* sibling);
        void attach(ASTNode* child);
        bool hasSibling;
        bool hasChild;

        ASTNode* getChild();
        linkNode* getSibling();
        linkNode* getTail();

    protected:
        ASTNode* ASTChildren;
        linkNode* sibling;
};

#endif