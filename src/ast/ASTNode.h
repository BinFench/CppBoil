#include "linkNode.h"
#include "../stack/stack.h"
#include "../parser/rule.h"
#include "../arg.h"
#include <type_traits>
#include <algorithm>
#include <functional>
#include <regex>
#include <string>

#ifndef ASTNODE_H
#define ASTNODE_H

class ASTNode
{
public:
    virtual bool parse(std::string *source, linkNode *path, std::string *str);
    virtual void *act(stack *values);
    std::string getId();

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

class anyNode : public ASTNode
{
public:
    anyNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
};

class anyOfNode : public ASTNode
{
public:
    template <typename... Args>
    anyOfNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

class charRangeNode : public ASTNode
{
public:
    charRangeNode(char begin, char end);
    charRangeNode(chNode *begin, chNode *end);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

class chNode : public ASTNode
{
public:
    char ch;
    chNode(char ch);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

class emptyNode : public ASTNode
{
public:
    emptyNode();
    bool parse(std::string *source, linkNode *path, std::string str);
};

class EOINode : public ASTNode
{
public:
    EOINode();
    bool parse(std::string *source, linkNode *path, std::string str);
};

class firstOfNode : public ASTNode
{
public:
    template <typename... Args>
    firstOfNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

class ignoreCaseNode : public ASTNode
{
public:
    ignoreCaseNode(char ch);
    ignoreCaseNode(chNode *ch);
    ignoreCaseNode(std::string str);
    ignoreCaseNode(stringNode *str);
    bool parse(std::string *source, linkNode *path, std::string *str);
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
};

class nothingNode : public ASTNode
{
public:
    nothingNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
};

class oneOrMoreNode : public ASTNode
{
public:
    oneOrMoreNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

class optionalNode : public ASTNode
{
public:
    optionalNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
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

class regexNode : public ASTNode
{
public:
    std::string str;
    regexNode(std::string str);
    bool parse(std::string *source, linkNode *path, std::string *last);
};

class sequenceNode : public ASTNode
{
public:
    template <typename... Args>
    sequenceNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

class stringNode : public ASTNode
{
public:
    std::string str;
    stringNode(std::string str);
    bool parse(std::string *source, linkNode *path, std::string *match);
};

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
};

class testNotNode : public ASTNode
{
public:
    testNotNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
};

class zeroOrMoreNode : public ASTNode
{
public:
    zeroOrMoreNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
};
#endif