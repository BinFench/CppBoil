/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: declarationg of parser.  Parser is base class for user to override
          and create their own rules.  Parser contains interface for the stack
          and the AST.
*/
#include "../ast/ASTNode.h"
#include "rule.h"
#include "../arg.h"
#include "../stack/stack.h"
#include <string>
#include <functional>

#ifndef PARSER_H
#define PARSER_H

ASTNode *makeNode(char ch);
ASTNode *makeNode(std::string str);
ASTNode *makeNode(rule *Rule);

class parser {
    //  Parser defines fundamental rules to build complex parsers and tokenizers.
public:
    stack *values;
    bool hasStack;

    parser();
    bool parse(std::string source, rule *root);
    void *getResult();
    ~parser();

    rule *any();
    template <typename... Args>
    rule *anyOf(Args... rules);
    rule *charRange(char begin, char end);
    rule *charRange(rule *begin, char end);
    rule *charRange(char begin, rule *end);
    rule *charRange(rule *begin, rule *end);
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

//  Pass any amount of children into anyOf rule.
template <typename... Args>
rule *parser::anyOf(Args... rules) {
    return new rule(new anyOfNode(makeNode(rules)...));
}

//  Pass any amount of children into firstOf rule.
template <typename... Args>
rule *parser::firstOf(Args... rules) {
    return new rule(new firstOfNode(makeNode(rules)...));
};

//  Pass either string or char or node into ignoreCase rule.
template <typename T>
rule *parser::ignoreCase(T text) {
    return new rule(new ignoreCaseNode(text));
}

//  Pass any amount of children into noneOf rule.
template <typename... Args>
rule *parser::noneOf(Args... rules) {
    return new rule(new noneOfNode(makeNode(rules)...));
}

//  Pass any amount of children into oneOrMore rule.
template <typename... Args>
rule *parser::oneOrMore(Args... rules) {
    return new rule(new oneOrMoreNode(makeNode(rules)...));
}

//  Pass any amount of arguments for push function.
template <typename... Args>
rule *parser::push(std::function<void *(arg *)> func, Args... Arg) {
    return push(func, new arg(Arg...));
}

//  Pass any amount of children to sequence rule.
template <typename... Args>
rule *parser::sequence(Args... rules) {
    return new rule(new sequenceNode(makeNode(rules)...));
}

//  Pass any amount of children to zeroOrMore rule.
template <typename... Args>
rule *parser::zeroOrMore(Args... rules) {
    return new rule(new zeroOrMoreNode(makeNode(rules)...));
}

//  Pass any amount of arguments for recursion function.
template <typename... Args>
rule *recursion(std::function<rule *(arg *)> func, Args... Arg) {
    return recursion(func, new arg(Arg...));
}

#endif