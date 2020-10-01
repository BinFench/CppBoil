#include "ASTNode.h"

class peekNode: public ASTNode {
    public:
        peekNode();
};
    
peekNode::peekNode() {
    id = "peek";
}