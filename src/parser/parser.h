#include "../ast/ASTNode.h"
#include "rule.h"
#include "../stack/stack.h"
#include <string>

class parser {
    public:
        stack *values;
        bool hasStack;

        parser();
        bool parse(std::string source, rule *root);

        rule *any();
        template<typename... Args>
        rule *anyOf(Args... rules);
        template<typename T, typename U>
        rule *charRange(T begin, U end);
        rule *ch(char cha);
        rule *empty();
        rule *EOI();
        template<typename... Args>
        rule *firstOf(Args... rules);
        template<typename T>
        rule *ignoreCase(T text);
        rule *match();
        template<typename... Args>
        rule *noneOf(Args... rules);
        rule *nothing();
        template<typename... Args>
        rule *oneOrMore(Args... rules);
        rule *optional(rule *text);
        rule *peek();
        rule *pop();
        rule *push(rule *text);
        rule *regex(std::string expr);
        template<typename... Args>
        rule *sequence(Args... rules);
        rule *String(std::string text);
        rule *swap();
        rule *test(rule *text);
        rule *testNot(rule *text);
        template<typename... Args>
        rule *zeroOrMore(Args... rules);
};