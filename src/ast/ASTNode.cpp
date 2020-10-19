#include "ASTNode.h"
#include "../arg.h"
#include <iostream>

ASTNode::ASTNode()
{
    id = "AST";
}

void ASTNode::populate(std::string type, ASTNode *node)
{
    if (id != type)
    {
        id = type;
        link = new linkNode();
        link->attach(node);
    }
    else
    {
        linkNode *sibling = new linkNode();
        sibling->attach(node);
        link->getTail()->append(sibling);
    }
}

void ASTNode::populate(std::string type, std::string node)
{
    populate(type, new stringNode(node));
}

void ASTNode::populate(std::string type, char node)
{
    populate(type, new chNode(node));
}

std::string ASTNode::getId()
{
    return id;
}

anyNode::anyNode()
{
    id = "any";
}

bool anyNode::parse(std::string *source, linkNode *path, std::string *str)
{
    if (source->length() > 0)
    {
        *str += source->at(0);
        source->erase(0, 1);
        return true;
    }
    std::cout << "ANY FAIL" << std::endl;
    return false;
}

void *anyNode::act(stack *values)
{
    return nullptr;
}

bool anyOfNode::parse(std::string *source, linkNode *path, std::string *str)
{
    linkNode *current = link;
    if (current->getChild()->parse(source, path, str))
    {
        return true;
    }
    while (current->hasSibling)
    {
        current = current->getSibling();
        if (current->getChild()->parse(source, path, str))
        {
            return true;
        }
    }
    std::cout << "ANYOF FAIL" << std::endl;
    return false;
}

void *anyOfNode::act(stack *values)
{
    return nullptr;
}

charRangeNode::charRangeNode(char begin, char end)
{
    populate("charRange", new chNode(begin), new chNode(end));
}

charRangeNode::charRangeNode(chNode *begin, char end)
{
    populate("charRange", begin, new chNode(end));
}

charRangeNode::charRangeNode(char begin, chNode *end)
{
    populate("charRange", new chNode(begin), end);
}

charRangeNode::charRangeNode(chNode *begin, chNode *end)
{
    populate("charRange", begin, end);
}

bool charRangeNode::parse(std::string *source, linkNode *path, std::string *str)
{
    if (source->length() == 0) return false;
    char max = ((chNode *)(link->getChild()))->ch;
    char min = ((chNode *)(link->getSibling()->getChild()))->ch;
    char temp;
    if (min > max)
    {
        temp = max;
        max = min;
        min = temp;
    }
    temp = source->at(0);

    std::cout << min << " <= " << temp << " <= " << max << std::endl;

    if (temp >= min && temp <= max)
    {
        *str += source->at(0);
        source->erase(0, 1);
        return true;
    }
    std::cout << "CHARRANGE FAIL" << std::endl;
    return false;
}

void *charRangeNode::act(stack *values)
{
    return nullptr;
}

chNode::chNode(char nch)
{
    id = "char";
    ch = nch;
}

bool chNode::parse(std::string *source, linkNode *path, std::string *str)
{
    if (source->length() == 0) return false;
    std::cout << source->at(0) << " == " << ch << std::endl;
    if (source->at(0) == ch)
    {
        std::cout << "Before: " << *source << std::endl;
        *str += source->at(0);
        source->erase(0, 1);
        std::cout << "After: " << *source << std::endl;
        return true;
    }
    std::cout << "CH FAIL" << std::endl;
    return false;
}

void *chNode::act(stack *values)
{
    return nullptr;
}

emptyNode::emptyNode()
{
    id = "empty";
}

bool emptyNode::parse(std::string *source, linkNode *path, std::string *str)
{
    return true;
}

void *emptyNode::act(stack *values)
{
    return nullptr;
}

EOINode::EOINode()
{
    id = "EOI";
}

bool EOINode::parse(std::string *source, linkNode *path, std::string *str)
{
    return (source->length() == 0);
}

void *EOINode::act(stack *values)
{
    return nullptr;
}

bool firstOfNode::parse(std::string *source, linkNode *path, std::string *str)
{
    linkNode *current = link;
    if (current->getChild()->parse(source, path, str))
    {
        return true;
    }
    while (current->hasSibling)
    {
        current = current->getSibling();
        if (current->getChild()->parse(source, path, str))
        {
            return true;
        }
    }
    std::cout << "FIRSTOF FAIL" << std::endl;
    return false;
}

void *firstOfNode::act(stack *values)
{
    return nullptr;
}

ignoreCaseNode::ignoreCaseNode(char ch)
{
    populate("ignoreCase", new chNode(ch));
}

ignoreCaseNode::ignoreCaseNode(chNode *ch)
{
    populate("ignoreCase", ch);
}

ignoreCaseNode::ignoreCaseNode(std::string str)
{
    populate("ignoreCase", new stringNode(str));
}

ignoreCaseNode::ignoreCaseNode(stringNode *str)
{
    populate("ignoreCase", str);
}

bool ignoreCaseNode::parse(std::string *source, linkNode *path, std::string *str)
{
    if (source->length() == 0) return false;
    if (link->getChild()->getId() == "char")
    {
        if (tolower(source->at(0)) == tolower(((chNode *)link->getChild())->ch))
        {
            *str += source->at(0);
            source->erase(0, 1);
            return true;
        }
        std::cout << "IGNORECASE FAIL" << std::endl;
        return false;
    }
    else
    {
        std::string data = ((stringNode *)link->getChild())->str;
        std::transform(data.begin(), data.end(), data.begin(),
                       [](unsigned char c) { return tolower(c); });

        std::string data2 = source->substr(0, data.length());
        std::transform(data2.begin(), data2.end(), data2.begin(),
                       [](unsigned char c) { return tolower(c); });

        if (data == data2)
        {
            *str += source->substr(0, data.length());
            source->erase(0, data.length());
            return true;
        }
        std::cout << "IGNORECASE FAIL" << std::endl;
        return false;
    }
}

void *ignoreCaseNode::act(stack *values)
{
    return nullptr;
}

matchNode::matchNode()
{
    id = "match";
}

bool matchNode::parse(std::string *source, linkNode *path, std::string *str)
{
    match = *str;
    linkNode *current = path->getTail();
    if (current->hasChild)
    {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    current->attach(this);

    return true;
}

void *matchNode::act(stack *values)
{
    return &match;
}

bool noneOfNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string *blank = new std::string;
    *blank = *str;
    linkNode *dummy = new linkNode();
    linkNode *current = link;
    std::string sample = *source;
    if (current->getChild()->parse(&sample, dummy, blank))
    {
        delete dummy;
        std::cout << "NONEOF FAIL" << std::endl;
        return false;
    }
    while (current->hasSibling)
    {
        current = current->getSibling();
        sample = *source;
        if (current->getChild()->parse(&sample, dummy, blank))
        {
            delete dummy;
            std::cout << "NONEOF FAIL" << std::endl;
            return false;
        }
    }
    *str += source->at(0);
    source->erase(0, 1);
    delete dummy;
    return true;
}

void *noneOfNode::act(stack *values)
{
    return nullptr;
}

nothingNode::nothingNode()
{
    id = "nothing";
}

bool nothingNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::cout << "NOTHING FAIL" << std::endl;
    return false;
}

void *nothingNode::act(stack *values)
{
    return nullptr;
}

oneOrMoreNode::oneOrMoreNode(ASTNode *node)
{
    populate("oneOrMore", node);
}

bool oneOrMoreNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string *blank = new std::string();
    *blank = *str;
    bool first = true;
    do
    {
        if (first && link->getChild()->parse(source, path, blank))
        {
            first = false;
        }
        else if (first)
        {
            std::cout << "ONEORMORE FAIL" << std::endl;
            return false;
        }
    } while (link->getChild()->parse(source, path, blank));
    std::cout << "oneOrMore: " << *source << std::endl;
    *str += *blank;
    return true;
}

void *oneOrMoreNode::act(stack *values)
{
    return nullptr;
}

optionalNode::optionalNode(ASTNode *node)
{
    populate("optional", node);
}

bool optionalNode::parse(std::string *source, linkNode *path, std::string *str)
{
    link->getChild()->parse(source, path, str);
    return true;
}

void *optionalNode::act(stack *values)
{
    return nullptr;
}

peekNode::peekNode()
{
    id = "peek";
}

bool peekNode::parse(std::string *source, linkNode *path, std::string *str)
{
    linkNode *current = path->getTail();
    if (current->hasChild)
    {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    current->attach(this);

    return true;
}

void *peekNode::act(stack *values)
{
    return values->peek();
}

popNode::popNode()
{
    id = "pop";
}

bool popNode::parse(std::string *source, linkNode *path, std::string *str)
{
    linkNode *current = path->getTail();
    if (current->hasChild)
    {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    current->attach(this);

    return true;
}

void *popNode::act(stack *values)
{
    return values->pop();
}

pushNode::pushNode(std::function<void *(arg *)> func, arg *nArg)
{
    id = "push";
    which = "func";
    argFunc = func;
    Arg = nArg;
    hasArgs = true;
}

pushNode::pushNode(std::function<void *()> nfunc)
{
    id = "push";
    which = "func";
    func = nfunc;
    Arg = Arg;
    hasArgs = false;
}

pushNode::pushNode(rule *text)
{
    id = "push";
    which = "match";
    match = text;
}

void *pushNode::push()
{
    if (which == "func")
    {
        if (hasArgs)
        {
            return argFunc(Arg);
        }
        return func();
    }
    if (match->getNode()->getId() == "match" || match->getNode()->getId() == "pop" || match->getNode()->getId() == "peek")
    {
        return match->getNode()->act(temp);
    }
    return match;
}

void *pushNode::act(stack *values)
{
    temp = values;
    if (which == "func" && Arg != nullptr)
    {
        Arg->values = values;
    }
    values->push(push());
    return values;
}

bool pushNode::parse(std::string *source, linkNode *path, std::string *str)
{
    linkNode *current = path->getTail();
    if (current->hasChild)
    {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    current->attach(this);

    if (which == "match")
    {
        linkNode *dummy = new linkNode();
        std::string *empty = new std::string();
        match->getNode()->parse(empty, dummy, str);
        
    }

    return true;
}

recursionNode::recursionNode(std::function<rule *()> nfunc)
{
    func = nfunc;
    hasArgs = false;
}

recursionNode::recursionNode(std::function<rule *(arg *)> func, arg *nArg)
{
    argFunc = func;
    Arg = nArg;
    hasArgs = true;
}

bool recursionNode::parse(std::string *source, linkNode *path, std::string *str)
{
    rule *eval;
    if (hasArgs)
    {
        eval = argFunc(Arg);
    }
    else
    {
        eval = func();
    }

    bool test = eval->getNode()->parse(source, path, str);
    delete eval;
    return test;
}

void *recursionNode::act(stack *values)
{
    return nullptr;
}

regexNode::regexNode(std::string nstr)
{
    id = "regex";
    str = nstr;
}

bool regexNode::parse(std::string *source, linkNode *path, std::string *last)
{
    try
    {
        std::regex rgx(str);
        std::smatch match;
        const std::string eval = *source;

        if (std::regex_search(eval.begin(), eval.end(), match, rgx) && source->find(match[1]) == 0)
        {
            *last += source->substr(0, match[1].length());
            source->erase(0, match[1].length());
            return true;
        }
        std::cout << "REGEX FAIL" << std::endl;
        return false;
    }
    catch (const std::regex_error &e)
    {
        std::cout << "regex_error caught: " << e.what() << std::endl;
        std::cout << "REGEX FAIL" << std::endl;
        return false;
    }
}

void *regexNode::act(stack *values)
{
    return nullptr;
}

bool sequenceNode::parse(std::string *source, linkNode *path, std::string *str)
{
    linkNode *current = link;
    std::string copy = *source;
    linkNode *dummy = new linkNode();
    std::string *blank = new std::string;
    std::string *temp = new std::string;
    std::string *ret = new std::string;
    *blank = *str;
    std::cout << "sequence: " << copy << std::endl;
    if (!current->getChild()->parse(&copy, dummy, blank))
    {
        delete dummy;
        std::cout << "SEQUENCE FAIL" << std::endl;
        return false;
    }
    std::cout << "sequence: " << copy << std::endl;
    *temp = *blank;
    *blank = blank->substr(str->length(), (blank->length() - str->length()));
    *ret = *temp;
    while (current->hasSibling)
    {
        current = current->getSibling();
        *temp = *blank;
        if (!current->getChild()->parse(&copy, dummy, blank))
        {
            delete dummy;
            std::cout << "SEQUENCE FAIL" << std::endl;
            return false;
        }
        std::cout << "sequence: " << copy << std::endl;
        *blank = blank->substr(temp->length(), (blank->length() - temp->length()));
        *ret += *blank;
    }

    *source = copy;
    path->getTail()->append(dummy);
    *str = *ret;
    return true;
}

void *sequenceNode::act(stack *values)
{
    return nullptr;
}

stringNode::stringNode(std::string nstr)
{
    id = "string";
    str = nstr;
}

bool stringNode::parse(std::string *source, linkNode *path, std::string *match)
{
    if (source->length() == 0) return false;
    if (source->find(str) == 0)
    {
        *match += source->substr(0, str.length());
        source->erase(0, str.length());
        return true;
    }
    std::cout << "STRING FAIL" << std::endl;
    return false;
}

void *stringNode::act(stack *values)
{
    return nullptr;
}

swapNode::swapNode()
{
    id = "swap";
}

bool swapNode::parse(std::string *source, linkNode *path, std::string *str)
{
    linkNode *current = path->getTail();
    if (current->hasChild)
    {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    current->attach(this);

    return true;
}

void *swapNode::act(stack *values)
{
    values->swap();
    return nullptr;
}

testNode::testNode(ASTNode *node)
{
    populate("test", node);
}

bool testNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string copy = *source;
    linkNode *dummy = new linkNode();
    std::string *temp = new std::string;
    *temp = *str;

    if (link->getChild()->parse(&copy, dummy, temp))
    {
        delete dummy;
        return true;
    }
    delete dummy;
    std::cout << "TEST FAIL" << std::endl;
    return false;
}

void *testNode::act(stack *values)
{
    return nullptr;
}

testNotNode::testNotNode(ASTNode *node)
{
    populate("testNot", node);
}

bool testNotNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string copy = *source;
    linkNode *dummy = new linkNode();
    std::string *temp = new std::string;
    *temp = *str;

    if (link->getChild()->parse(&copy, dummy, temp))
    {
        delete dummy;
        std::cout << "TESTNOT FAIL" << std::endl;
        return false;
    }
    delete dummy;
    return true;
}

void *testNotNode::act(stack *values)
{
    return nullptr;
}

zeroOrMoreNode::zeroOrMoreNode(ASTNode *node)
{
    populate("zeroOrMore", node);
}

bool zeroOrMoreNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string *blank = new std::string();
    *blank = *str;
    bool first = true;
    do
    {
        if (first && link->getChild()->parse(source, path, blank))
        {
            first = false;
        }
        else if (first)
        {
            return true;
        }
    } while (link->getChild()->parse(source, path, blank));
    *str += *blank;
    return true;
}

void *zeroOrMoreNode::act(stack *values)
{
    return nullptr;
}