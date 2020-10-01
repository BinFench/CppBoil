#include "ASTNode.h"

class pushNode: public ASTNode {
    public:
        pushNode();
};
    
pushNode::pushNode() {
    id = "push";
}