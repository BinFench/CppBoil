#include "parser.h"
#include "rule.h"
#include <string>

parser::parser(){};
bool parser::parse(std::string source, rule root){};

rule parser::any(){};
template <typename... Args>
rule parser::anyOf(Args... rules){};
template <typename T, typename U>
rule parser::charRange(T begin, U end){};
rule parser::ch(char cha){};
rule parser::empty(){};
rule parser::EOI(){};
template <typename... Args>
rule parser::firstOf(Args... rules){};
template <typename T>
rule parser::ignoreCase(T text){};
rule parser::match(){};
template <typename... Args>
rule parser::noneOf(Args... rules){};
rule parser::nothing(){};
template <typename... Args>
rule parser::oneOrMore(Args... rules){};
rule parser::optional(rule text){};
rule parser::peek(){};
rule parser::pop(){};
rule parser::push(rule text){};
rule parser::regex(std::string expr){};
template <typename... Args>
rule parser::sequence(Args... rules){};
rule parser::String(std::string text){};
rule parser::swap(){};
rule parser::test(rule text){};
rule parser::testNot(rule text){};
template <typename... Args>
rule parser::zeroOrMore(Args... rules){};