#include "ASTNode.h"

class nothingNode : public ASTNode
{
public:
    nothingNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
};

nothingNode::nothingNode()
{
    id = "nothing";
}

bool nothingNode::parse(std::string *source, linkNode *path, std::string *str)
{
    return false;
}