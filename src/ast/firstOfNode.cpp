#include "ASTNode.h"

class firstOfNode: public ASTNode {
    public:
        template<typename... Args>
        firstOfNode(Args... nodes);
        bool parse(std::string *source, linkNode* path);
};
    
template<typename... Args>
firstOfNode::firstOfNode(Args... nodes) {
    populate("firstOf", nodes...);
}

bool firstOfNode::parse(std::string *source, linkNode* path) {
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