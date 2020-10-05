#include "ASTNode.h"

class noneOfNode: public ASTNode {
    public:
        template<typename... Args>
        noneOfNode(Args... nodes);
};
    
template<typename... Args>
noneOfNode::noneOfNode(Args... nodes) {
    populate("noneOf", nodes...);
}