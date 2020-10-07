#include "ASTNode.h"

class anyNode: public ASTNode {
    public:
        anyNode();
        bool parse(std::string *source, linkNode* path);
};
    
anyNode::anyNode() {
    id = "any";
}

bool anyNode::parse(std::string *source, linkNode* path) {
    if (source->length() > 0) {
        source->erase(0, 1);
        return true;
    }
    return false;
}