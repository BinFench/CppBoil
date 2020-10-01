#include "ASTNode.h"

class emptyNode: public ASTNode {
    public:
        emptyNode();
};
    
emptyNode::emptyNode() {
    id = "empty";
}