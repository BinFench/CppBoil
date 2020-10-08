#include "ASTNode.h"

class zeroOrMoreNode : public ASTNode
{
public:
    zeroOrMoreNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

zeroOrMoreNode::zeroOrMoreNode(ASTNode *node)
{
    populate("zeroOrMore", node);
}

bool zeroOrMoreNode::parse(std::string *source, linkNode *path, std::string *str)
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
            return true;
        }
    } while (link->getChild()->parse(source, path, blank));
    *str += *blank;
    return true;
}