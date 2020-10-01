class ASTNode;

class linkNode {
    friend class ASTNode;

    protected:
        ASTNode* ASTChildren;
        linkNode* sibling;
        bool hasSibling;
        bool hasChild;

        linkNode();
        void append(linkNode* sibling);
        void attach(ASTNode* child);
}