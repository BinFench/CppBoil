#include "ASTNode.h"

#ifndef MATCHNODE_CPP
#define MATCHNODE_CPP
class matchNode : public ASTNode
{
public:
    matchNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);

protected:
    std::string match;
};

matchNode::matchNode()
{
    id = "match";
}

bool matchNode::parse(std::string *source, linkNode *path, std::string *str)
{
    match = *str;
    linkNode *current = path->getTail();
    if (current->hasChild)
    {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    current->attach(this);

    return true;
}

void *matchNode::act(stack *values)
{
    return &match;
}
#endif