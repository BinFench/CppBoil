#include "ASTNode.h"

#ifndef PEEKNODE_CPP
#define PEEKNODE_CPP
class peekNode : public ASTNode
{
public:
    peekNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

peekNode::peekNode()
{
    id = "peek";
}

bool peekNode::parse(std::string *source, linkNode *path, std::string *str)
{
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

void *peekNode::act(stack *values)
{
    return values->peek();
}
#endif