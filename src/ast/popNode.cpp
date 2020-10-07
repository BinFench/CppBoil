#include "ASTNode.h"

class popNode: public ASTNode {
    public:
        popNode();
        bool parse(std::string *source, linkNode* path);
};
    
popNode::popNode() {
    id = "pop";
}

bool popNode::parse(std::string *source, linkNode *path) {
    linkNode *current = path->getTail();
    if (current->hasChild) {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    current->attach(this);

    return true;
}