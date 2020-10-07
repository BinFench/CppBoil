#include "ASTNode.h"

class testNode: public ASTNode {
    public:
        testNode(ASTNode *node);
        bool parse(std::string *source, linkNode* path);
};
    
testNode::testNode(ASTNode *node) {
    populate("test", node);
}

bool testNode::parse(std::string *source, linkNode *path) {
    std::string copy = *source;
    linkNode *dummy = new linkNode();

    if (link->getChild()->parse(&copy, dummy)) {
        delete dummy;
        return true;
    }
    delete dummy;
    return false;
}