class ASTNode;

#ifndef RULE_H
#define RULE_H
class rule {
    public:
        rule(ASTNode *node);
        ASTNode* getNode();
        ~rule();

    protected:
        ASTNode *node;
};

#endif