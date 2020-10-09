#include "ASTNode.h"

#ifndef EMPTYNODE_CPP
#define EMPTYNODE_CPP
class emptyNode : public ASTNode
{
public:
    emptyNode();
    bool parse(std::string *source, linkNode *path, std::string str);
};

emptyNode::emptyNode()
{
    id = "empty";
}

bool emptyNode::parse(std::string *source, linkNode *path, std::string str)
{
    return true;
}
#endif