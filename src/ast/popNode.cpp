#include "ASTNode.h"

class popNode: public ASTNode {
    public:
        popNode();
};
    
popNode::popNode() {
    id = "pop";
}