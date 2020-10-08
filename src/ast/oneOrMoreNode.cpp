#include "ASTNode.h"

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