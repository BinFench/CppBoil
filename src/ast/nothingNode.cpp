#include "ASTNode.h"

class nothingNode: public ASTNode {
    public:
        nothingNode();
};
    
nothingNode::nothingNode() {
    id = "nothing";
}