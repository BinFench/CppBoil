#include "ASTNode.h"

class peekNode : public ASTNode
{
public:
    peekNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
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