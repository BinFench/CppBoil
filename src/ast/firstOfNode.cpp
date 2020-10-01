#include "ASTNode.h"

class firstOfNode: public ASTNode {
    public:
        template<typename... Args>
        firstOfNode(Args... nodes);
};
    
template<typename... Args>
firstOfNode::firstOfNode(Args... nodes) {
    populate("firstOf", nodes);
}