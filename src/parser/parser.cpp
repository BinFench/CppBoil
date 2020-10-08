#include "../stack/stack.h"
#include "parser.h"
#include "rule.h"
#include "../ast/anyNode.cpp"
#include "../ast/anyOfNode.cpp"
#include "../ast/charRangeNode.cpp"
#include "../ast/chNode.cpp"
#include "../ast/emptyNode.cpp"
#include "../ast/EOINode.cpp"
#include "../ast/firstOfNode.cpp"
#include "../ast/ignoreCaseNode.cpp"
#include "../ast/matchNode.cpp"
#include "../ast/noneOfNode.cpp"
#include "../ast/nothingNode.cpp"
#include "../ast/oneOrMoreNode.cpp"
#include "../ast/optionalNode.cpp"
#include "../ast/peekNode.cpp"
#include "../ast/popNode.cpp"
#include "../ast/pushNode.cpp"
#include "../ast/regexNode.cpp"
#include "../ast/sequenceNode.cpp"
#include "../ast/stringNode.cpp"
#include "../ast/swapNode.cpp"
#include "../ast/testNode.cpp"
#include "../ast/testNotNode.cpp"
#include "../ast/zeroOrMoreNode.cpp"
#include "../ast/recursionNode.cpp"
#include "../arg.h"
#include <type_traits>
#include <functional>

parser::parser()
{
    hasStack = false;
}

bool parser::parse(std::string source, rule *root)
{
    linkNode *parsePath = new linkNode();
    std::string *str;
    if (((ASTNode *)(root->getNode()))->parse(&source, parsePath, str))
    {
        if (!hasStack)
        {
            values = new stack();
        }
        else
        {
            delete values;
            values = new stack();
        }
        hasStack = true;

        linkNode *current = parsePath;
        current->getChild()->act(values);
        while (current->hasSibling)
        {
            current = current->getSibling();
            current->getChild()->act(values);
        }

        delete parsePath;
        return true;
    }

    return false;
}

void *parser::getResult() {
    return values->pop();
}

rule *parser::any()
{
    return new rule(new anyNode());
}

template <typename... Args>
rule *parser::anyOf(Args... rules)
{
    return new rule(new anyOfNode(rules...->getNode()));
}

template <typename T, typename U>
rule *parser::charRange(T begin, U end)
{
    chNode *a;
    chNode *b;
    if (std::is_same<T, char>::value)
    {
        a = new chNode(begin);
    }
    else if (std::is_same<T, chNode>::value)
    {
        a = begin;
    }

    if (std::is_same<U, char>::value)
    {
        b = new chNode(end);
    }
    else if (std::is_same<U, chNode>::value)
    {
        b = end;
    }

    return new rule(new charRangeNode(a, b));
}

rule *parser::ch(char cha)
{
    return new rule(new chNode(cha));
}

rule *parser::empty()
{
    return new rule(new emptyNode());
}

rule *parser::EOI()
{
    return new rule(new EOINode());
}

template <typename... Args>
rule *parser::firstOf(Args... rules)
{
    return new rule(new firstOfNode(rules...->getNode()));
};

template <typename T>
rule *parser::ignoreCase(T text)
{
    return new rule(new ignoreCaseNode(text));
}

rule *parser::match()
{
    return new rule(new matchNode());
}

template <typename... Args>
rule *parser::noneOf(Args... rules)
{
    return new rule(new noneOfNode(rules...->getNode()));
}

rule *parser::nothing()
{
    return new rule(new nothingNode());
}

template <typename... Args>
rule *parser::oneOrMore(Args... rules)
{
    return new rule(new oneOrMoreNode(rules...->getNode()));
}

rule *parser::optional(rule *text)
{
    return new rule(new optionalNode((ASTNode *)(text->getNode())));
}

rule *parser::peek()
{
    return new rule(new peekNode());
}

rule *parser::pop()
{
    return new rule(new popNode());
}

rule *parser::push(std::function<void *(arg *)> func, arg *Arg)
{
    return new rule(new pushNode(func, Arg));
}

template <typename... Args>
rule *parser::push(std::function<void *(arg *)> func, Args... Arg)
{
    return push(func, new arg(Arg...));
}

rule *parser::push(rule *text)
{
    return new rule(new pushNode(text));
}

rule *parser::regex(std::string expr)
{
    return new rule(new regexNode(expr));
}

template <typename... Args>
rule *parser::sequence(Args... rules)
{
    return new rule(new sequenceNode(rules...->getNode()));
}

rule *parser::String(std::string text)
{
    return new rule(new stringNode(text));
}

rule *parser::swap()
{
    return new rule(new swapNode());
}

rule *parser::test(rule *text)
{
    return new rule(new testNode((ASTNode *)text->getNode()));
}

rule *parser::testNot(rule *text)
{
    return new rule(new testNotNode((ASTNode *)text->getNode()));
}

template <typename... Args>
rule *parser::zeroOrMore(Args... rules)
{
    return new rule(new zeroOrMoreNode(rules...->getNode()));
}

rule *parser::recursion(std::function<rule *(arg *)> func, arg *Arg)
{
    return new rule(new recursionNode(func, Arg));
}

rule *parser::recursion(std::function<rule *()> func)
{
    return new rule(new recursionNode(func));
}

template <typename... Args>
rule *recursion(std::function<rule *(arg *)> func, Args... Arg)
{
    return recursion(func, new arg(Arg...));
}