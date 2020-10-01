#include "ASTNode.h"

class anyOfNode: public ASTNode {
    public:
        template<typename... Args>
        anyOfNode(Args... nodes);
};
    
template<typename... Args>
anyOfNode::anyOfNode(Args... nodes) {
    populate("anyOf", nodes);
}