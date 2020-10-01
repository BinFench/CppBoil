#include "ASTNode.h"

class oneOrMoreNode: public ASTNode {
    public:
        oneOrMoreNode(ASTNode *node);
};
    
oneOrMoreNode::oneOrMoreNode(ASTNode *node) {
    populate("oneOrMore", node);
}