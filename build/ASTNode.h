#include "linkNode.h"
#include "stack.h"
#include "rule.h"
#include <type_traits>
#include <algorithm>
#include <functional>
#include <regex>
#include <string>

#ifndef ASTNODE_H
#define ASTNODE_H
class arg;

class ASTNode
{
public:
    virtual bool parse(std::string *source, linkNode *path, std::string *str) { return false; };
    virtual void *act(stack *values) { return nullptr; };
    std::string getId();
    ASTNode();

protected:
    std::string id;
    linkNode *link;

    template <typename... Args>
    void populate(std::string type, ASTNode *node, Args... nodes);
    template <typename... Args>
    void populate(std::string type, std::string node, Args... nodes);
    template <typename... Args>
    void populate(std::string type, char node, Args... nodes);
    void populate(std::string type, ASTNode *node);
    void populate(std::string type, std::string node);
    void populate(std::string type, char node);
};

class chNode : public ASTNode
{
public:
    char ch;
    chNode(char ch);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class stringNode : public ASTNode
{
public:
    std::string str;
    stringNode(std::string str);
    bool parse(std::string *source, linkNode *path, std::string *match);
    void *act(stack *values);
};

template <typename... Args>
void ASTNode::populate(std::string type, ASTNode *node, Args... nodes)
{
    if (id != type)
    {
        id = type;
        link = new linkNode();
        link->attach(node);
    }
    else
    {
        linkNode *sibling = new linkNode();
        sibling->attach(node);
        link->getTail()->append(sibling);
    }
    populate(type, nodes...);
}

template <typename... Args>
void ASTNode::populate(std::string type, std::string node, Args... nodes)
{
    if (id != type)
    {
        id = type;
        link = new linkNode();
        link->attach(new stringNode(node));
    }
    else
    {
        linkNode *sibling = new linkNode();
        sibling->attach(new stringNode(node));
        link->getTail()->append(sibling);
    }
    populate(type, nodes...);
}

template <typename... Args>
void ASTNode::populate(std::string type, char node, Args... nodes)
{
    if (id != type)
    {
        id = type;
        link = new linkNode();
        link->attach(new chNode(node));
    }
    else
    {
        linkNode *sibling = new linkNode();
        sibling->attach(new chNode(node));
        link->getTail()->append(sibling);
    }
    populate(type, nodes...);
}

class anyNode : public ASTNode
{
public:
    anyNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class anyOfNode : public ASTNode
{
public:
    template <typename... Args>
    anyOfNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

template <typename... Args>
anyOfNode::anyOfNode(Args... nodes)
{
    populate("anyOf", nodes...);
}

class charRangeNode : public ASTNode
{
public:
    charRangeNode(char begin, char end);
    charRangeNode(chNode *begin, char end);
    charRangeNode(char begin, chNode *end);
    charRangeNode(chNode *begin, chNode *end);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class emptyNode : public ASTNode
{
public:
    emptyNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class EOINode : public ASTNode
{
public:
    EOINode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class firstOfNode : public ASTNode
{
public:
    template <typename... Args>
    firstOfNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

template <typename... Args>
firstOfNode::firstOfNode(Args... nodes)
{
    populate("firstOf", nodes...);
}

class ignoreCaseNode : public ASTNode
{
public:
    ignoreCaseNode(char ch);
    ignoreCaseNode(chNode *ch);
    ignoreCaseNode(std::string str);
    ignoreCaseNode(stringNode *str);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class matchNode : public ASTNode
{
public:
    matchNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);

protected:
    std::string match;
};

class noneOfNode : public ASTNode
{
public:
    template <typename... Args>
    noneOfNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

template <typename... Args>
noneOfNode::noneOfNode(Args... nodes)
{
    populate("noneOf", nodes...);
}

class nothingNode : public ASTNode
{
public:
    nothingNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class oneOrMoreNode : public ASTNode
{
public:
    oneOrMoreNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class optionalNode : public ASTNode
{
public:
    optionalNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class peekNode : public ASTNode
{
public:
    peekNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class popNode : public ASTNode
{
public:
    popNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

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

template <typename... Args>
pushNode::pushNode(std::function<void *(arg *)> func, Args... Arg)
{
    pushNode(func, new arg(Arg...));
}

class recursionNode : public ASTNode
{
public:
    recursionNode(std::function<rule *()> func);
    recursionNode(std::function<rule *(arg *)> func, arg *Arg);
    template <typename... Args>
    recursionNode(std::function<rule *(arg *)> func, Args... Arg);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);

protected:
    std::function<rule *(arg *)> argFunc;
    std::function<rule *()> func;
    bool hasArgs;
    arg *Arg;
};

template <typename... Args>
recursionNode::recursionNode(std::function<rule *(arg *)> func, Args... Arg)
{
    recursionNode(func, new arg(Arg...));
}

class regexNode : public ASTNode
{
public:
    std::string str;
    regexNode(std::string str);
    bool parse(std::string *source, linkNode *path, std::string *last);
    void *act(stack *values);
};

class sequenceNode : public ASTNode
{
public:
    template <typename... Args>
    sequenceNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

template <typename... Args>
sequenceNode::sequenceNode(Args... nodes)
{
    populate("sequence", nodes...);
}

class swapNode : public ASTNode
{
public:
    swapNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class testNode : public ASTNode
{
public:
    testNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class testNotNode : public ASTNode
{
public:
    testNotNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};

class zeroOrMoreNode : public ASTNode
{
public:
    zeroOrMoreNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
};
#endif