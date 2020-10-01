#include "ASTNode.h"

class matchNode: public ASTNode {
    public:
        matchNode();
};
    
matchNode::matchNode() {
    id = "match";
}