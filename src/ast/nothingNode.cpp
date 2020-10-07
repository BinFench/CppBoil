#include "ASTNode.h"

class nothingNode: public ASTNode {
    public:
        nothingNode();
        bool parse(std::string *source, linkNode* path);
};
    
nothingNode::nothingNode() {
    id = "nothing";
}

bool nothingNode::parse(std::string *source, linkNode *path) {
    return false;
}