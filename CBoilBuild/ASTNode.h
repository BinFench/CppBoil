/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: declaration of AST nodes.
          ASTNodes implement their own rules for parsing,
          such as a sequence of other rules or one or more
          occurences of sub rules.
*/
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

//  Forward declaration, see arg.h
class arg;

class ASTNode {
    //  The parent class, contains all the common functions and members to be overridden.
public:
    virtual bool parse(std::string *source, linkNode *path, std::string *str) { return false; };
    virtual void *act(stack *values) { return nullptr; };
    virtual ASTNode *copy() {return nullptr;};
    std::string getId();
    ASTNode();
    virtual ~ASTNode() {}

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

class chNode : public ASTNode {
    //  Node for matching a single char.
public:
    chNode();
    char ch;
    chNode(char ch);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    chNode *copy();
};

class stringNode : public ASTNode {
    //  Node for matching a string
public:
    stringNode();
    std::string str;
    stringNode(std::string str);
    bool parse(std::string *source, linkNode *path, std::string *match);
    void *act(stack *values);
    stringNode *copy();
};

/*
  Parametric recursion function.  Constructs tree with parent 
  node and n number of children.
*/
template <typename... Args>
void ASTNode::populate(std::string type, ASTNode *node, Args... nodes) {
    if (id != type) {
        id = type;
        link = new linkNode();
        link->attach(node);
    }
    else {
        linkNode *sibling = new linkNode();
        sibling->attach(node);
        link->getTail()->append(sibling);
    }
    //  Parametric recursion: Function is called with one less parameter.
    populate(type, nodes...);
}

//  Same as above function, but string is converted to stringNode.
template <typename... Args>
void ASTNode::populate(std::string type, std::string node, Args... nodes) {
    if (id != type) {
        id = type;
        link = new linkNode();
        link->attach(new stringNode(node));
    } else {
        linkNode *sibling = new linkNode();
        sibling->attach(new stringNode(node));
        link->getTail()->append(sibling);
    }
    populate(type, nodes...);
}

//  Same as above function, but char is converted to chNode.
template <typename... Args>
void ASTNode::populate(std::string type, char node, Args... nodes) {
    if (id != type) {
        id = type;
        link = new linkNode();
        link->attach(new chNode(node));
    } else {
        linkNode *sibling = new linkNode();
        sibling->attach(new chNode(node));
        link->getTail()->append(sibling);
    }
    populate(type, nodes...);
}

class anyNode : public ASTNode {
    //  Node for matching any char
public:
    anyNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    anyNode *copy();
};

class anyOfNode : public ASTNode {
    //  Node for matching any subnode.
public:
    anyOfNode();
    template <typename... Args>
    anyOfNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    anyOfNode *copy();
    ~anyOfNode();
};

//  Uses parametric recursion to construct tree.
template <typename... Args>
anyOfNode::anyOfNode(Args... nodes) {
    populate("anyOf", nodes...);
}

class charRangeNode : public ASTNode {
    //  Node to match any char in a range.
public:
    charRangeNode();
    charRangeNode(char begin, char end);
    charRangeNode(chNode *begin, char end);
    charRangeNode(char begin, chNode *end);
    charRangeNode(chNode *begin, chNode *end);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    charRangeNode *copy();
    ~charRangeNode();
};

class emptyNode : public ASTNode {
    //  Node to match anything.
public:
    emptyNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    emptyNode *copy();
};

class EOINode : public ASTNode {
    //  Node to match end of input (empty string).
public:
    EOINode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    EOINode *copy();
};

class firstOfNode : public ASTNode {
    //  Node to match first accepted subnode.
public:
    firstOfNode();
    template <typename... Args>
    firstOfNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    firstOfNode *copy();
    ~firstOfNode();
};

//  Uses parametric recursion to construct tree.
template <typename... Args>
firstOfNode::firstOfNode(Args... nodes) {
    populate("firstOf", nodes...);
}

class ignoreCaseNode : public ASTNode {
    //  Node to match a char or string despite capitalization.
public:
    ignoreCaseNode();
    ignoreCaseNode(char ch);
    ignoreCaseNode(chNode *ch);
    ignoreCaseNode(std::string str);
    ignoreCaseNode(stringNode *str);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    ignoreCaseNode *copy();
    ~ignoreCaseNode();
};

class matchNode : public ASTNode {
    //  Stack action node.  stores last matched string.
public:
    matchNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    matchNode *copy();

protected:
    std::string match;
};

class noneOfNode : public ASTNode {
    //  Node to match any character that doesn't pass any subnodes.
public:
    noneOfNode();
    template <typename... Args>
    noneOfNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    noneOfNode *copy();
    ~noneOfNode();
};

//  Uses parametric recursion to construct tree.
template <typename... Args>
noneOfNode::noneOfNode(Args... nodes) {
    populate("noneOf", nodes...);
}

class nothingNode : public ASTNode {
    //  Node that matches nothing.
public:
    nothingNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    nothingNode *copy();
};

class oneOrMoreNode : public ASTNode {
    //  Node that matches at least one occurance of subnode.
public:
    oneOrMoreNode();
    oneOrMoreNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    oneOrMoreNode *copy();
    ~oneOrMoreNode();
};

class optionalNode : public ASTNode {
    //  Node that always matches, optionally matches subnode.
public:
    optionalNode();
    optionalNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    optionalNode *copy();
    ~optionalNode();
};

class peekNode : public ASTNode {
    //  Stack action node.  Gets reference to item at top of stack.
public:
    peekNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    peekNode *copy();
};

class popNode : public ASTNode {
    //  Stack action node.  Pops item from top of stack.
public:
    popNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    popNode *copy();
};

class pushNode : public ASTNode {
    //  Stack action node.  Pushes item to top of stack.
public:
    pushNode();
    pushNode(std::function<void *(arg *)> func, arg *Arg);
    template <typename... Args>
    pushNode(std::function<void *(arg *)> func, Args... Arg);
    pushNode(std::function<void *()> func);
    pushNode(rule *text);
    void *act(stack *values);
    void *push();
    bool parse(std::string *source, linkNode *path, std::string *str);
    pushNode *copy();
    ~pushNode();

protected:
    std::function<void *(arg *)> argFunc;
    std::function<void *()> func;
    bool hasArgs;
    rule *match;
    std::string which;
    arg *Arg;
    stack *temp;
};

//  Uses parametric recursion to construct tree.
template <typename... Args>
pushNode::pushNode(std::function<void *(arg *)> func, Args... Arg) {
    pushNode(func, new arg(Arg...));
}

class recursionNode : public ASTNode {
    //  Node to match parent node.  Prevents infinite recursive loop.
public:
    recursionNode();
    recursionNode(std::function<rule *()> func);
    recursionNode(std::function<rule *(arg *)> func, arg *Arg);
    template <typename... Args>
    recursionNode(std::function<rule *(arg *)> func, Args... Arg);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    recursionNode *copy();
    ~recursionNode();

protected:
    std::function<rule *(arg *)> argFunc;
    std::function<rule *()> func;
    bool hasArgs;
    arg *Arg;
};

//  Uses parametric recursion to construct tree.
template <typename... Args>
recursionNode::recursionNode(std::function<rule *(arg *)> func, Args... Arg) {
    recursionNode(func, new arg(Arg...));
}

class regexNode : public ASTNode {
    //  Node to match string to regular expression.
public:
    regexNode();
    std::string str;
    regexNode(std::string str);
    bool parse(std::string *source, linkNode *path, std::string *last);
    void *act(stack *values);
    regexNode *copy();
};

class sequenceNode : public ASTNode {
    //  Node to match string to sequence of sub nodes.
public:
    sequenceNode();
    template <typename... Args>
    sequenceNode(Args... nodes);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    sequenceNode *copy();
    ~sequenceNode();
};

//  Uses parametric recursion to construct tree.
template <typename... Args>
sequenceNode::sequenceNode(Args... nodes) {
    populate("sequence", nodes...);
}

class swapNode : public ASTNode {
    //  Stack action node.  Swaps item at top of stack with item below.
public:
    swapNode();
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    swapNode *copy();
};

class testNode : public ASTNode {
    //  Node that tests if string matches subnode.  Does not update parse state.
public:
    testNode();
    testNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    testNode *copy();
    ~testNode();
};

class testNotNode : public ASTNode {
    //  Node that tests if string fails subnode.  Does not update parse state.
public:
    testNotNode();
    testNotNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    testNotNode *copy();
    ~testNotNode();
};

class zeroOrMoreNode : public ASTNode {
    //  Node that matches zero or multiple occurrances of sub nodes.
public:
    zeroOrMoreNode();
    zeroOrMoreNode(ASTNode *node);
    bool parse(std::string *source, linkNode *path, std::string *str);
    void *act(stack *values);
    zeroOrMoreNode *copy();
    ~zeroOrMoreNode();
};
#endif