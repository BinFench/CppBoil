#include "ASTNode.h"

#ifndef SWAPNODE_CPP
#define SWAPNODE_CPP
class swapNode : public ASTNode
{
public:
    swapNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

swapNode::swapNode()
{
    id = "swap";
}

bool swapNode::parse(std::string *source, linkNode *path, std::string *str)
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

void *swapNode::act(stack *values)
{
    values->swap();
    return nullptr;
}
#endif