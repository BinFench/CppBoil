#include "ASTNode.h"

class testNotNode: public ASTNode {
    public:
        testNotNode(ASTNode *node);
};
    
testNotNode::testNotNode(ASTNode *node) {
    populate("testNot", node);
}