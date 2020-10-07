#include "ASTNode.h"

class sequenceNode: public ASTNode {
    public:
        template<typename... Args>
        sequenceNode(Args... nodes);
        bool parse(std::string *source, linkNode* path);
};
    
template<typename... Args>
sequenceNode::sequenceNode(Args... nodes) {
    populate("sequence", nodes...);
}

bool sequenceNode::parse(std::string *source, linkNode *path) {
    linkNode *current = link;
    std::string copy = *source;
    linkNode *dummy = new linkNode();
    if (!current->getChild()->parse(&copy, dummy)) {
        delete dummy;
        return false;
    }
    while (current->hasSibling) {
        current = current->getSibling();
        if (!current->getChild()->parse(&copy, dummy)) {
            delete dummy;
            return false;
        }
    }

    source = &copy;
    path->getTail()->append(dummy);
    return true;
}