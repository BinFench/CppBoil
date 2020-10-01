#include "ASTNode.h"

class testNode: public ASTNode {
    public:
        testNode(ASTNode *node);
};
    
testNode::testNode(ASTNode *node) {
    populate("test", node);
}