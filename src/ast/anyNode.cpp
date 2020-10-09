#include "ASTNode.h"

#ifndef ANYNODE_CPP
#define ANYNODE_CPP
class anyNode : public ASTNode
{
public:
    anyNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
};

anyNode::anyNode()
{
    id = "any";
}

bool anyNode::parse(std::string *source, linkNode *path, std::string *str)
{
    if (source->length() > 0)
    {
        *str += source->at(0);
        source->erase(0, 1);
        return true;
    }
    return false;
}
#endif