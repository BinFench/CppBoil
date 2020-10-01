#include <ASTNode.h>

class anyNode: public ASTNode {
    public:
        template<class ASTNode, class... ASTNode>
        anyNode(ASTNode node, ASTNode... nodes);
        anyNode(ASTNode node);
}

template<class... ASTNode>
anyNode(ASTNode... nodes) {

}