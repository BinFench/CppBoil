#include "ASTNode.h"

#ifndef ONEORMORENODE_CPP
#define ONEORMORENODE_CPP
class oneOrMoreNode : public ASTNode
{
public:
    oneOrMoreNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

oneOrMoreNode::oneOrMoreNode(ASTNode *node)
{
    populate("oneOrMore", node);
}

bool oneOrMoreNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string *blank;
    *blank = *str;
    bool first = true;
    do
    {
        if (first && link->getChild()->parse(source, path, blank))
        {
            first = false;
        }
        else if (first)
        {
            return false;
        }
    } while (link->getChild()->parse(source, path, blank));
    *str += *blank;
    return true;
}
#endif