#include "ASTNode.h"

class sequenceNode: public ASTNode {
    public:
        template<typename... Args>
        sequenceNode(Args... nodes);
};
    
template<typename... Args>
sequenceNode::sequenceNode(Args... nodes) {
    populate("sequence", nodes...);
}