#include "ASTNode.h"
#include <functional>
#include "../parser/rule.h"
#include "../arg.h"

#ifndef PUSHNODE_CPP
#define PUSHNODE_CPP
class pushNode : public ASTNode
{
public:
    pushNode(std::function<void *(arg *)> func, arg *Arg);
    template <typename... Args>
    pushNode(std::function<void *(arg *)> func, Args... Arg);
    pushNode(std::function<void *()> func);
    pushNode(rule *text);
    void *act(stack *values);
    void *push();
    bool parse(std::string *source, linkNode *path, std::string *str);

protected:
    std::function<void *(arg *)> argFunc;
    std::function<void *()> func;
    bool hasArgs;
    rule *match;
    std::string which;
    arg *Arg;
    stack *temp;
};

pushNode::pushNode(std::function<void *(arg *)> func, arg *Arg)
{
    id = "push";
    which = "func";
    argFunc = func;
    Arg = Arg;
    hasArgs = true;
}

template <typename... Args>
pushNode::pushNode(std::function<void *(arg *)> func, Args... Arg)
{
    pushNode(func, new arg(Arg...));
}

pushNode::pushNode(std::function<void *()> func)
{
    id = "push";
    which = "func";
    func = func;
    Arg = Arg;
    hasArgs = false;
}

pushNode::pushNode(rule *text)
{
    id = "push";
    which = "match";
    match = text;
}

void *pushNode::push()
{
    if (which == "func")
    {
        if (hasArgs)
        {
            return argFunc(Arg);
        }
        return func();
    }
    if (match->getNode()->getId() == "match" || match->getNode()->getId() == "pop" || match->getNode()->getId() == "peek")
    {
        return match->getNode()->act(temp);
    }
    return match;
}

void *pushNode::act(stack *values)
{
    temp = values;
    if (which == "func" && Arg != nullptr)
    {
        Arg->values = values;
    }
    values->push(push());
    return values;
}

bool pushNode::parse(std::string *source, linkNode *path, std::string *str)
{
    linkNode *current = path->getTail();
    if (current->hasChild)
    {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    current->attach(this);

    if (which == "match")
    {
        linkNode *dummy = new linkNode();
        std::string *empty;
        match->getNode()->parse(empty, dummy, str);
    }

    return true;
}
#endif