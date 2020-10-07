#include "ASTNode.h"

class optionalNode: public ASTNode {
    public:
        optionalNode(ASTNode *node);
        bool parse(std::string *source, linkNode* path);
};
    
optionalNode::optionalNode(ASTNode *node) {
    populate("optional", node);
}

bool optionalNode::parse(std::string *source, linkNode *path) {
    link->getChild()->parse(source, path);
    return true;
}