#include "../ast/ASTNode.h"
#include "rule.h"
#include "../stack/stack.h"
#include "../arg.h"
#include <string>
#include <functional>

#ifndef PARSER_H
#define PARSER_H

class parser
{
public:
    stack *values;
    bool hasStack;

    parser();
    bool parse(std::string source, rule *root);
    void *getResult();

    rule *any();
    template <typename... Args>
    rule *anyOf(Args... rules);
    template <typename T, typename U>
    rule *charRange(T begin, U end);
    rule *ch(char cha);
    rule *empty();
    rule *EOI();
    template <typename... Args>
    rule *firstOf(Args... rules);
    template <typename T>
    rule *ignoreCase(T text);
    rule *match();
    template <typename... Args>
    rule *noneOf(Args... rules);
    rule *nothing();
    template <typename... Args>
    rule *oneOrMore(Args... rules);
    rule *optional(rule *text);
    rule *peek();
    rule *pop();
    rule *push(std::function<void *(arg *)> func, arg *Arg);
    template <typename... Args>
    rule *push(std::function<void *(arg *)> func, Args... Arg);
    rule *push(rule *text);
    rule *regex(std::string expr);
    template <typename... Args>
    rule *sequence(Args... rules);
    rule *String(std::string text);
    rule *swap();
    rule *test(rule *text);
    rule *testNot(rule *text);
    template <typename... Args>
    rule *zeroOrMore(Args... rules);
    rule *recursion(std::function<rule *(arg *)> func, arg *Arg);
    template <typename... Args>
    rule *recursion(std::function<rule *(arg *)> func, Args... Arg);
    rule *recursion(std::function<rule *()> func);
};

#endif