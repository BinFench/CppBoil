#include "parser.h"
#include <iostream>

ASTNode *makeNode(char ch) {
    return new chNode(ch);
}

ASTNode *makeNode(std::string str) {
    return new stringNode(str);
}

ASTNode *makeNode(rule *Rule) {
    ASTNode *toRet = Rule->getNode();
    delete Rule;
    return toRet;
}

parser::parser() {
    hasStack = false;
}

bool parser::parse(std::string source, rule *root) {
    linkNode *parsePath = new linkNode();
    std::string *str = new std::string();
    std::string *src = new std::string();
    *src = source;
    ASTNode *node = root->getNode();
    if (node->parse(src, parsePath, str)) {
        std::cout << "Done parsing" << std::endl;
        if (!hasStack) {
            values = new stack();
        } else {
            delete values;
            values = new stack();
        }
        hasStack = true;

        linkNode *current = parsePath;
        if (current->hasChild) {
            current->getChild()->act(values);
            //current->hasChild = false;
        }
        while (current->hasSibling) {
            current = current->getSibling();
            if (current->hasChild) {
                current->getChild()->act(values);
                //current->hasChild = false;
            }
        }

        std::cout << "Done acting" << std::endl;
        delete parsePath;
        std::cout << "Done parsePath" << std::endl;
        delete node;
        delete root;
        delete str;
        return true;
    }

    delete parsePath;
    delete node;
    delete root;
    delete str;
    return false;
}

void *parser::getResult() {
    void *toRet = values->pop();
    return toRet;
}

rule *parser::any() {
    return new rule(new anyNode());
}

rule *parser::ch(char cha) {
    return new rule(new chNode(cha));
}

rule *parser::charRange(char begin, char end) {
    return new rule(new charRangeNode(begin, end));
}

rule *parser::charRange(rule *begin, char end) {
    return new rule(new charRangeNode((chNode *)begin->getNode(), end));
}

rule *parser::charRange(char begin, rule *end) {
    return new rule(new charRangeNode(begin, (chNode *)end->getNode()));
}

rule *parser::charRange(rule *begin, rule *end) {
    return new rule(new charRangeNode((chNode *)begin->getNode(), (chNode *)end->getNode()));
}

rule *parser::empty() {
    return new rule(new emptyNode());
}

rule *parser::EOI() {
    return new rule(new EOINode());
}

rule *parser::match() {
    return new rule(new matchNode());
}

rule *parser::nothing() {
    return new rule(new nothingNode());
}

rule *parser::optional(rule *text) {
    return new rule(new optionalNode((ASTNode *)(text->getNode())));
}

rule *parser::peek() {
    return new rule(new peekNode());
}

rule *parser::pop() {
    return new rule(new popNode());
}

rule *parser::push(std::function<void *(arg *)> func, arg *Arg) {
    return new rule(new pushNode(func, Arg));
}

rule *parser::push(rule *text) {
    return new rule(new pushNode(text));
}

rule *parser::regex(std::string expr) {
    return new rule(new regexNode(expr));
}

rule *parser::String(std::string text) {
    return new rule(new stringNode(text));
}

rule *parser::swap() {
    return new rule(new swapNode());
}

rule *parser::test(rule *text) {
    return new rule(new testNode((ASTNode *)text->getNode()));
}

rule *parser::testNot(rule *text) {
    return new rule(new testNotNode((ASTNode *)text->getNode()));
}

rule *parser::recursion(std::function<rule *(arg *)> func, arg *Arg) {
    return new rule(new recursionNode(func, Arg));
}

rule *parser::recursion(std::function<rule *()> func) {
    return new rule(new recursionNode(func));
}

parser::~parser() {
    delete values;
}