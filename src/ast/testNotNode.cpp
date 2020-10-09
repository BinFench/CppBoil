#include "ASTNode.h"

#ifndef TESTNOTNODE_CPP
#define TESTNOTNODE_CPP
class testNotNode : public ASTNode
{
public:
    testNotNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

testNotNode::testNotNode(ASTNode *node)
{
    populate("testNot", node);
}

bool testNotNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string copy = *source;
    linkNode *dummy = new linkNode();
    std::string *temp;
    *temp = *str;

    if (link->getChild()->parse(&copy, dummy, temp))
    {
        delete dummy;
        return false;
    }
    delete dummy;
    return true;
}
#endif