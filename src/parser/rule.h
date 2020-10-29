class ASTNode;

#ifndef RULE_H
#define RULE_H

class rule {
    public:
        rule() {};
        rule(ASTNode *node);
        ASTNode* getNode();
        rule *copy();

    protected:
        ASTNode *node;
};

#endif