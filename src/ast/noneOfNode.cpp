#include "ASTNode.h"

class noneOfNode: public ASTNode {
    public:
        template<typename... Args>
        noneOfNode(Args... nodes);
        bool parse(std::string *source, linkNode* path);
};
    
template<typename... Args>
noneOfNode::noneOfNode(Args... nodes) {
    populate("noneOf", nodes...);
}

bool noneOfNode::parse(std::string *source, linkNode* path) {
    linkNode *dummy = new linkNode();
    linkNode *current = link;
    std::string sample = *source;
    if (current->getChild()->parse(&sample, dummy)) {
        delete dummy;
        return false;
    }
    while (current->hasSibling) {
        current = current->getSibling();
        sample = *source;
        if (current->getChild()->parse(&sample, dummy)) {
            delete dummy;
            return false;
        }
    }
    source->erase(0, 1);
    delete dummy;
    return true;
}