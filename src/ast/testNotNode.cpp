#include "ASTNode.h"

class testNotNode: public ASTNode {
    public:
        testNotNode(ASTNode *node);
        bool parse(std::string *source, linkNode* path);
};
    
testNotNode::testNotNode(ASTNode *node) {
    populate("testNot", node);
}

bool testNotNode::parse(std::string *source, linkNode *path) {
    std::string copy = *source;
    linkNode *dummy = new linkNode();

    if (link->getChild()->parse(&copy, dummy)) {
        delete dummy;
        return false;
    }
    delete dummy;
    return true;
}