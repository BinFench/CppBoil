#include "ASTNode.h"

class testNode : public ASTNode
{
public:
    testNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

testNode::testNode(ASTNode *node)
{
    populate("test", node);
}

bool testNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string copy = *source;
    linkNode *dummy = new linkNode();
    std::string *temp;

    if (link->getChild()->parse(&copy, dummy, temp))
    {
        delete dummy;
        return true;
    }
    delete dummy;
    return false;
}