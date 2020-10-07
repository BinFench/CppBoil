#include "ASTNode.h"

class matchNode: public ASTNode {
    public:
        matchNode();
        bool parse(std::string *source, linkNode* path);
};
    
matchNode::matchNode() {
    id = "match";
}

bool matchNode::parse(std::string *source, linkNode* path) {
    linkNode *current = path->getTail();
    if (current->hasChild) {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    current->attach(this);

    return true;
}