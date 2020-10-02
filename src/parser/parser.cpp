#include <string>
#include "../stack/stack.h"
#include "../ast/ASTNode.h"
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

parser::parser() {
    hasStack = false;
}

bool parser::parse(std::string source, rule *root) {
    return true;
}

rule *parser::any() {
    return new rule((ASTNode*)new anyNode());
}

template <typename... Args>
rule *parser::anyOf(Args... rules) {}

template <typename T, typename U>
rule *parser::charRange(T begin, U end) {}

rule *parser::ch(char cha) {
    return new rule((ASTNode*)new chNode(cha));
}

rule *parser::empty() {
    return new rule((ASTNode*)new emptyNode());
}

rule *parser::EOI() {
    return new rule((ASTNode*)new EOINode());
}

template <typename... Args>
rule *parser::firstOf(Args... rules) {};

template <typename T>
rule *parser::ignoreCase(T text) {}

rule *parser::match() {
    return new rule((ASTNode*)new matchNode());
}

template <typename... Args>
rule *parser::noneOf(Args... rules) {}

rule *parser::nothing() {
    return new rule((ASTNode*)new nothingNode());
}

template <typename... Args>
rule *parser::oneOrMore(Args... rules) {}

rule *parser::optional(rule *text) {
    return new rule((ASTNode*)new optionalNode((ASTNode*)(text->getNode())));
}

rule *parser::peek() {
    return new rule((ASTNode*)new peekNode());
}

rule *parser::pop() {
    return new rule((ASTNode*)new popNode());
}

rule *parser::push(rule *text) {
    return new rule((ASTNode*)new pushNode());
}

rule *parser::regex(std::string expr) {
    return new rule((ASTNode*)new regexNode(expr));
}

template <typename... Args>
rule *parser::sequence(Args... rules) {}

rule *parser::String(std::string text) {
    return new rule((ASTNode*)new stringNode(text));
}

rule *parser::swap() {
    return new rule((ASTNode*)new swapNode());
}

rule *parser::test(rule *text) {
    return new rule((ASTNode*)new testNode((ASTNode*)text->getNode()));
}

rule *parser::testNot(rule *text) {
    return new rule((ASTNode*)new testNotNode((ASTNode*)text->getNode()));
}

template <typename... Args>
rule *parser::zeroOrMore(Args... rules) {}