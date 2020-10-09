#include "ASTNode.h"
#include <string>
#include <regex>

#ifndef REGEXNODE_CPP
#define REGEXNODE_CPP
class regexNode : public ASTNode
{
public:
    std::string str;
    regexNode(std::string str);
    bool parse(std::string *source, linkNode *path, std::string *last);
};

regexNode::regexNode(std::string str)
{
    id = "regex";
    str = str;
}

bool regexNode::parse(std::string *source, linkNode *path, std::string *last)
{
    std::regex rgx(str);
    std::smatch match;
    const std::string eval = *source;

    if (std::regex_search(eval.begin(), eval.end(), match, rgx) && source->find(match[1]) == 0)
    {
        *last += source->substr(0, match[1].length());
        source->erase(0, match[1].length());
        return true;
    }
    return false;
}
#endif