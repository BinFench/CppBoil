#include "ASTNode.h"
#include "chNode.cpp"
#include <algorithm>

#ifndef CHARRANGENODE_CPP
#define CHARRANGENODE_CPP
class charRangeNode : public ASTNode
{
public:
    charRangeNode(char begin, char end);
    charRangeNode(chNode *begin, chNode *end);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

charRangeNode::charRangeNode(char begin, char end)
{
    populate("charRange", new chNode(begin), new chNode(end));
}

charRangeNode::charRangeNode(chNode *begin, chNode *end)
{
    populate("charRange", begin, end);
}

bool charRangeNode::parse(std::string *source, linkNode *path, std::string *str)
{
    char max = ((chNode *)(link->getChild()))->ch;
    char min = ((chNode *)(link->getSibling()->getChild()))->ch;
    char temp;
    if (min > max)
    {
        temp = max;
        max = min;
        min = temp;
    }
    temp = source->at(0);

    if (temp >= min && temp <= max)
    {
        *str += source->at(0);
        source->erase(0, 1);
        return true;
    }
    return false;
}
#endif