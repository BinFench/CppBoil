#include "ASTNode.h"

#ifndef CHNODE_CPP
#define CHNODE_CPP

class chNode : public ASTNode
{
public:
    char ch;
    chNode(char ch);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

chNode::chNode(char ch)
{
    id = "char";
    ch = ch;
}

bool chNode::parse(std::string *source, linkNode *path, std::string *str)
{
    if (source->at(0) == ch)
    {
        *str += source->at(0);
        source->erase(0, 1);
        return true;
    }
    return false;
}

#endif