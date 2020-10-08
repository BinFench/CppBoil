#include "ASTNode.h"

class sequenceNode : public ASTNode
{
public:
    template <typename... Args>
    sequenceNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

template <typename... Args>
sequenceNode::sequenceNode(Args... nodes)
{
    populate("sequence", nodes...);
}

bool sequenceNode::parse(std::string *source, linkNode *path, std::string *str)
{
    linkNode *current = link;
    std::string copy = *source;
    linkNode *dummy = new linkNode();
    std::string *blank;
    std::string *temp;
    std::string *ret;
    *blank = *str;
    if (!current->getChild()->parse(&copy, dummy, blank))
    {
        delete dummy;
        return false;
    }
    *temp = *blank;
    *blank = blank->substr(str->length(), (blank->length() - str->length()));
    *ret = *temp;
    while (current->hasSibling)
    {
        current = current->getSibling();
        *temp = *blank;
        if (!current->getChild()->parse(&copy, dummy, blank))
        {
            delete dummy;
            return false;
        }
        *blank = blank->substr(temp->length(), (blank->length() - temp->length()));
        *ret += *blank;
    }

    source = &copy;
    path->getTail()->append(dummy);
    *str = *ret;
    return true;
}