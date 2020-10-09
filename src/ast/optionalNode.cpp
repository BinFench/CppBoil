#include "ASTNode.h"

#ifndef OPTIONALNODE_CPP
#define OPTIONALNODE_CPP
class optionalNode : public ASTNode
{
public:
    optionalNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

optionalNode::optionalNode(ASTNode *node)
{
    populate("optional", node);
}

bool optionalNode::parse(std::string *source, linkNode *path, std::string *str)
{
    link->getChild()->parse(source, path, str);
    return true;
}
#endif