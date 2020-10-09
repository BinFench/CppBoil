#include "ASTNode.h"

#ifndef FIRSTOF_CPP
#define FIRSTOF_CPP
class firstOfNode : public ASTNode
{
public:
    template <typename... Args>
    firstOfNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

template <typename... Args>
firstOfNode::firstOfNode(Args... nodes)
{
    populate("firstOf", nodes...);
}

bool firstOfNode::parse(std::string *source, linkNode *path, std::string *str)
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