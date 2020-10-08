#include "ASTNode.h"

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