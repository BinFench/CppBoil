#include "ASTNode.h"

class optionalNode: public ASTNode {
    public:
        optionalNode(ASTNode node);
};
    
optionalNode::optionalNode(ASTNode node) {
    populate("optional", node);
}