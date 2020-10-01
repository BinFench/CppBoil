#include "ASTNode.h"

class zeroOrMoreNode: public ASTNode {
    public:
        zeroOrMoreNode(ASTNode *node);
};
    
zeroOrMoreNode::zeroOrMoreNode(ASTNode *node) {
    populate("zeroOrMore", node);
}