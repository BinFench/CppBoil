#include "ASTNode.h"

#ifndef ANYOFNODE_CPP
#define ANYOFNODE_CPP
class anyOfNode : public ASTNode
{
public:
    template <typename... Args>
    anyOfNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

template <typename... Args>
anyOfNode::anyOfNode(Args... nodes)
{
    populate("anyOf", nodes...);
}

bool anyOfNode::parse(std::string *source, linkNode *path, std::string *str)
{
    linkNode *current = link;
    if (current->getChild()->parse(source, path, str))
    {
        return true;
    }
    while (current->hasSibling)
    {
        current = current->getSibling();
        if (current->getChild()->parse(source, path, str))
        {
            return true;
        }
    }
    return false;
}
#endif