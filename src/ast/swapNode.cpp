#include "ASTNode.h"

class swapNode: public ASTNode {
    public:
        swapNode();
        bool parse(std::string *source, linkNode* path);
};
    
swapNode::swapNode() {
    id = "swap";
}

bool swapNode::parse(std::string *source, linkNode *path) {
    linkNode *current = path->getTail();
    if (current->hasChild) {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    current->attach(this);

    return true;
}