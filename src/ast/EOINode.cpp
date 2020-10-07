#include "ASTNode.h"

class EOINode: public ASTNode {
    public:
        EOINode();
        bool parse(std::string *source, linkNode* path);
};
    
EOINode::EOINode() {
    id = "EOI";
}

bool EOINode::parse(std::string *source, linkNode *path) {
    return (source->length() == 0);
}