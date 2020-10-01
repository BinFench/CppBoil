#include "ASTNode.h"

class EOINode: public ASTNode {
    public:
        EOINode();
};
    
EOINode::EOINode() {
    id = "EOI";
}