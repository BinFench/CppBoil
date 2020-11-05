/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: implementation of parser defined in parser.h.  Parser is base class
          for user to override and create their own rules.  Parser contains
          interface for the stack and the AST.
*/
#include "parser.h"

//  Utility function to make node out of char.
ASTNode *makeNode(char ch) {
    return new chNode(ch);
}

//  Utility function to make node out of string.
ASTNode *makeNode(std::string str) {
    return new stringNode(str);
}

//  Utility function to get node out of rule, and delete rule for memory save.
ASTNode *makeNode(rule *Rule) {
    ASTNode *toRet = Rule->getNode();
    Rule->hasNode = false;
    delete Rule;
    return toRet;
}

parser::parser() {
    hasStack = false;
}

/*
  Parsing function.  Parses given string based on given rule.
  After parsing, the stack is built and processed based on rule parse.
  Returns true for successful match, false otherwise.
  source: The string to parse.
  root: The rule to match against source.
*/
bool parser::parse(std::string source, rule *root) {
    //  parsePath is the linked list of stack actions for after parsing.
    linkNode *parsePath = new linkNode();
    //  str holds the matched string.  After successful parse, should match source.
    std::string *str = new std::string();
    std::string *src = new std::string();
    *src = source;
    ASTNode *node = root->getNode();
    if (node->parse(src, parsePath, str)) {
        //  After successful parse, create empty stack.
        if (!hasStack) {
            values = new stack();
        } else {
            delete values;
            values = new stack();
        }
        hasStack = true;

        linkNode *current = parsePath;
        if (current->hasChild) {
            //  Act on stack.
            current->getChild()->act(values);
        }
        //  Traverse siblings and act on stack.
        while (current->hasSibling) {
            current = current->getSibling();
            if (current->hasChild) {
                current->getChild()->act(values);
            }
        }

        delete parsePath;
        //  TODO: Fix memory leaks without segfault.
        delete node;
        delete root;
        delete str;
        delete src; 
        return true;
    }

    delete parsePath;
    //  TODO: Fix memory leaks without segfault.
    delete node;
    delete root;
    delete str;
    delete src;
    return false;
}

//  Push item from top of stack.  Use after parsing.
void *parser::getResult() {
    void *toRet = values->pop();
    return toRet;
}

//  Rule to accept any char.
rule *parser::any() {
    return new rule(new anyNode());
}

//  Rule to match specific char.
rule *parser::ch(char cha) {
    return new rule(new chNode(cha));
}

//  Rule to match char withing range.
rule *parser::charRange(char begin, char end) {
    return new rule(new charRangeNode(begin, end));
}

rule *parser::charRange(rule *begin, char end) {
    return new rule(new charRangeNode((chNode *)makeNode(begin), end));
}

rule *parser::charRange(char begin, rule *end) {
    return new rule(new charRangeNode(begin, (chNode *)makeNode(end)));
}

rule *parser::charRange(rule *begin, rule *end) {
    return new rule(new charRangeNode((chNode *)makeNode(begin), (chNode *)makeNode(end)));
}

//  Rule to always accept.
rule *parser::empty() {
    return new rule(new emptyNode());
}

//  Rule to match empty string.
rule *parser::EOI() {
    return new rule(new EOINode());
}

//  Rule to store last parsed string.
rule *parser::match() {
    return new rule(new matchNode());
}

//  Rule to never accept.
rule *parser::nothing() {
    return new rule(new nothingNode());
}

//  Rule to always accept, match subrule if it passes.
rule *parser::optional(rule *text) {
    return new rule(new optionalNode(makeNode(text)));
}

//  Rule to get reference to item at top of stack.
rule *parser::peek() {
    return new rule(new peekNode());
}

//  Rule to get item at top of stack.
rule *parser::pop() {
    return new rule(new popNode());
}

//  Rule to push item on stack.
rule *parser::push(std::function<void *(arg *)> func, arg *Arg) {
    return new rule(new pushNode(func, Arg));
}

rule *parser::push(rule *text) {
    return new rule(new pushNode(text));
}

//  Rule to match string to regular expression.
rule *parser::regex(std::string expr) {
    return new rule(new regexNode(expr));
}

//  Rule to match specific string.
rule *parser::String(std::string text) {
    return new rule(new stringNode(text));
}

//  Rule to swap item at top of stack with item below.
rule *parser::swap() {
    return new rule(new swapNode());
}

//  Rule to test if parse passes subrule without updating parse state.
rule *parser::test(rule *text) {
    return new rule(new testNode(makeNode(text)));
}

//  Rule to test if parse fails subrule without updating parse state.
rule *parser::testNot(rule *text) {
    return new rule(new testNotNode(makeNode(text)));
}

//  Rule to parse string with parent rule.  Use to prevent infinite recursion.
rule *parser::recursion(std::function<rule *(arg *)> func, arg *Arg) {
    return new rule(new recursionNode(func, Arg));
}

rule *parser::recursion(std::function<rule *()> func) {
    return new rule(new recursionNode(func));
}

parser::~parser() {
    delete values;
}