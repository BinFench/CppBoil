#include "ASTNode.h"

class anyNode: public ASTNode {
    public:
        anyNode();
};
    
anyNode::anyNode() {
    id = "any";
}