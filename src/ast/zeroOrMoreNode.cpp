#include "ASTNode.h"

class zeroOrMoreNode: public ASTNode {
    public:
        zeroOrMoreNode(ASTNode *node);
        bool parse(std::string *source, linkNode* path);
};
    
zeroOrMoreNode::zeroOrMoreNode(ASTNode *node) {
    populate("zeroOrMore", node);
}

bool zeroOrMoreNode::parse(std::string *source, linkNode *path) {
    bool first = true;
    do {
        if (first && link->getChild()->parse(source, path)) {
            first = false;
        } else if (first) {
            return true;
        }
    } while (link->getChild()->parse(source, path));
    return true;
}