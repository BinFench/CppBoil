#include "ASTNode.h"

#ifndef EOINODE_CPP
#define EOINODE_CPP
class EOINode : public ASTNode
{
public:
    EOINode();
    bool parse(std::string *source, linkNode *path, std::string str);
};

EOINode::EOINode()
{
    id = "EOI";
}

bool EOINode::parse(std::string *source, linkNode *path, std::string str)
{
    return (source->length() == 0);
}
#endif