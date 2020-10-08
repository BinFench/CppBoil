#include "ASTNode.h"
#include <functional>
#include "../parser/rule.h"
#include "../arg.h"

class recursionNode : public ASTNode
{
public:
    recursionNode(std::function<rule *()> func);
    recursionNode(std::function<rule *(arg *)> func, arg *Arg);
    template <typename... Args>
    recursionNode(std::function<rule *(arg *)> func, Args... Arg);
    bool parse(std::string *source, linkNode *path, std::string *str);

protected:
    std::function<rule *(arg *)> argFunc;
    std::function<rule *()> func;
    bool hasArgs;
    arg *Arg;
};

recursionNode::recursionNode(std::function<rule *()> func)
{
    func = func;
    hasArgs = false;
}

recursionNode::recursionNode(std::function<rule *(arg *)> func, arg *Arg)
{
    argFunc = func;
    Arg = Arg;
    hasArgs = true;
}

template <typename... Args>
recursionNode::recursionNode(std::function<rule *(arg *)> func, Args... Arg)
{
    recursionNode(func, new arg(Arg...));
}

bool recursionNode::parse(std::string *source, linkNode *path, std::string *str)
{
    rule *eval;
    if (hasArgs)
    {
        eval = argFunc(Arg);
    }
    else
    {
        eval = func();
    }

    bool test = eval->getNode()->parse(source, path, str);
    delete eval;
    return test;
}