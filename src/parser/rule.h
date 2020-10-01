#include "../ast/ASTNode.h"

class rule {
    public:
        rule(ASTNode *node);
        ASTNode* getNode();

    protected:
        ASTNode *node;
};