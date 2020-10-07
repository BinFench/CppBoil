#include "ASTNode.h"

class anyOfNode: public ASTNode {
    public:
        template<typename... Args>
        anyOfNode(Args... nodes);
        bool parse(std::string *source, linkNode* path);
};
    
template<typename... Args>
anyOfNode::anyOfNode(Args... nodes) {
    populate("anyOf", nodes...);
}

bool anyOfNode::parse(std::string *source, linkNode* path) {
    linkNode *current = link;
    if (current->getChild()->parse(source, path)) {
        return true;
    }
    while (current->hasSibling) {
        current = current->getSibling();
        if (current->getChild()->parse(source, path)) {
            return true;
        }
    }
    return false;
}