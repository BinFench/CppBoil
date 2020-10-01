class ASTNode;

class linkNode {
    public:
        linkNode();
        void append(linkNode* sibling);
        void attach(ASTNode* child);

    protected:
        ASTNode* ASTChildren;
        linkNode* sibling;
        bool hasSibling;
        bool hasChild;
};