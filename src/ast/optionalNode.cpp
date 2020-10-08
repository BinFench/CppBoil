#include "ASTNode.h"

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