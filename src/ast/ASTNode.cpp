#include "ASTNode.h"
#include "../arg.h"
#include <iostream>

ASTNode::ASTNode() {
    id = "AST";
}

void ASTNode::populate(std::string type, ASTNode *node) {
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

void ASTNode::populate(std::string type, std::string node) {
    populate(type, new stringNode(node));
}

void ASTNode::populate(std::string type, char node) {
    populate(type, new chNode(node));
}

std::string ASTNode::getId() {
    return id;
}

anyNode::anyNode() {
    id = "any";
}

bool anyNode::parse(std::string *source, linkNode *path, std::string *str) {
    if (source->length() > 0) {
        *str = source->at(0);
        source->erase(0, 1);
        return true;
    }
    *str = "";
    return false;
}

void *anyNode::act(stack *values) {
    return nullptr;
}

anyNode *anyNode::copy() {
    return new anyNode;
}

anyOfNode::anyOfNode() {
    id = "anyOf";
}

bool anyOfNode::parse(std::string *source, linkNode *path, std::string *str) {
    linkNode *current = link;
    std::string *copy = new std::string;
    *copy = *str;
    if (current->getChild()->parse(source, path, copy)) {
        *str = *copy;
        delete copy;
        return true;
    }
    while (current->hasSibling) {
        current = current->getSibling();
        if (current->getChild()->parse(source, path, copy)) {
            *str = *copy;
            delete copy;
            return true;
        }
    }
    *str = "";
    delete copy;
    return false;
}

void *anyOfNode::act(stack *values) {
    return nullptr;
}

anyOfNode *anyOfNode::copy() {
    anyOfNode *toRet = new anyOfNode();
    toRet->link = link->copy();
    return toRet;
}

anyOfNode::~anyOfNode() {
    delete link;
}

charRangeNode::charRangeNode() {
    id = "charRange";
}

charRangeNode::charRangeNode(char begin, char end) {
    populate("charRange", new chNode(begin), new chNode(end));
}

charRangeNode::charRangeNode(chNode *begin, char end) {
    populate("charRange", begin, new chNode(end));
}

charRangeNode::charRangeNode(char begin, chNode *end) {
    populate("charRange", new chNode(begin), end);
}

charRangeNode::charRangeNode(chNode *begin, chNode *end) {
    populate("charRange", begin, end);
}

bool charRangeNode::parse(std::string *source, linkNode *path, std::string *str) {
    if (source->length() == 0) {
        *str = "";
        return false;
    }
    char max = ((chNode *)(link->getChild()))->ch;
    char min = ((chNode *)(link->getSibling()->getChild()))->ch;
    char temp;
    if (min > max) {
        temp = max;
        max = min;
        min = temp;
    }
    temp = source->at(0);

    if (temp >= min && temp <= max) {
        *str = source->at(0);
        source->erase(0, 1);
        return true;
    }
    *str = "";
    return false;
}

void *charRangeNode::act(stack *values) {
    return nullptr;
}

charRangeNode *charRangeNode::copy() {
    charRangeNode *toRet = new charRangeNode();
    toRet->link = link->copy();
    return toRet;
}

charRangeNode::~charRangeNode() {
    delete link;
}

chNode::chNode() {
    id = "char";
}

chNode::chNode(char nch) {
    id = "char";
    ch = nch;
}

bool chNode::parse(std::string *source, linkNode *path, std::string *str) {
    if (source->length() == 0) {
        *str = "";
        return false;
    }
    if (source->at(0) == ch) {
        *str = source->at(0);
        source->erase(0, 1);
        return true;
    }
    *str = "";
    return false;
}

void *chNode::act(stack *values) {
    return nullptr;
}

chNode *chNode::copy() {
    chNode *toRet = new chNode();
    toRet->ch = ch;
    return toRet;
}

emptyNode::emptyNode() {
    id = "empty";
}

bool emptyNode::parse(std::string *source, linkNode *path, std::string *str) {
    *str = "";
    return true;
}

void *emptyNode::act(stack *values) {
    return nullptr;
}

emptyNode *emptyNode::copy() {
    return new emptyNode();
}

EOINode::EOINode() {
    id = "EOI";
}

bool EOINode::parse(std::string *source, linkNode *path, std::string *str) {
    if (source->length() == 0) {
        *str = "";
        return true;
    }
    *str = "";
    return false;
}

void *EOINode::act(stack *values) {
    return nullptr;
}

EOINode *EOINode::copy() {
    return new EOINode();
}

firstOfNode::firstOfNode() {
    id = "firstOf";
}

bool firstOfNode::parse(std::string *source, linkNode *path, std::string *str) {
    linkNode *current = link;
    std::string *copy = new std::string();
    *copy = *str;
    if (current->getChild()->parse(source, path, copy)) {
        *str = *copy;
        delete copy;
        return true;
    }
    while (current->hasSibling) {
        current = current->getSibling();
        if (current->getChild()->parse(source, path, copy)) {
            *str = *copy;
            delete copy;
            return true;
        }
    }
    *str = "";
    delete copy;
    return false;
}

void *firstOfNode::act(stack *values) {
    return nullptr;
}

firstOfNode *firstOfNode::copy() {
    firstOfNode *toRet = new firstOfNode();
    toRet->link = link->copy();
    return toRet;
}

firstOfNode::~firstOfNode() {
    delete link;
}

ignoreCaseNode::ignoreCaseNode() {
    id = "ignoreCase";
}

ignoreCaseNode::ignoreCaseNode(char ch) {
    populate("ignoreCase", new chNode(ch));
}

ignoreCaseNode::ignoreCaseNode(chNode *ch) {
    populate("ignoreCase", ch);
}

ignoreCaseNode::ignoreCaseNode(std::string str) {
    populate("ignoreCase", new stringNode(str));
}

ignoreCaseNode::ignoreCaseNode(stringNode *str) {
    populate("ignoreCase", str);
}

bool ignoreCaseNode::parse(std::string *source, linkNode *path, std::string *str) {
    if (source->length() == 0) {
        *str = "";
        return false;
    }
    if (link->getChild()->getId() == "char") {
        if (tolower(source->at(0)) == tolower(((chNode *)link->getChild())->ch)) {
            *str = source->at(0);
            source->erase(0, 1);
            return true;
        }
        *str = "";
        return false;
    } else {
        std::string data = ((stringNode *)link->getChild())->str;
        std::transform(data.begin(), data.end(), data.begin(),
                       [](unsigned char c) { return tolower(c); });

        std::string data2 = source->substr(0, data.length());
        std::transform(data2.begin(), data2.end(), data2.begin(),
                       [](unsigned char c) { return tolower(c); });

        if (data == data2) {
            *str = source->substr(0, data.length());
            source->erase(0, data.length());
            return true;
        }
        *str = "";
        return false;
    }
}

void *ignoreCaseNode::act(stack *values) {
    return nullptr;
}

ignoreCaseNode *ignoreCaseNode::copy() {
    ignoreCaseNode *toRet = new ignoreCaseNode();
    toRet->link = link->copy();
    return toRet;
}

ignoreCaseNode::~ignoreCaseNode() {
    delete link;
}

matchNode::matchNode() {
    id = "match";
}

bool matchNode::parse(std::string *source, linkNode *path, std::string *str) {
    match = *str;
    linkNode *current = path->getTail();
    if (current->hasChild) {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    matchNode *clone = copy();
    current->attach(clone);

    *str = "";
    return true;
}

void *matchNode::act(stack *values) {
    std::string *toRet = new std::string();
    *toRet = match;
    return static_cast<void *>(toRet);
}

matchNode *matchNode::copy() {
    matchNode *toRet = new matchNode();
    toRet->match = match;
    return toRet;
}

noneOfNode::noneOfNode() {
    id = "noneOf";
}

bool noneOfNode::parse(std::string *source, linkNode *path, std::string *str) {
    std::string *blank = new std::string;
    *blank = *str;
    linkNode *dummy = new linkNode();
    linkNode *current = link;
    std::string *sample = new std::string;
    *sample = *source;
    if (current->getChild()->parse(sample, dummy, blank)) {
        delete dummy;
        *str = "";
        delete blank;
        return false;
    }
    while (current->hasSibling) {
        current = current->getSibling();
        *sample = *source;
        if (current->getChild()->parse(sample, dummy, blank)) {
            delete dummy;
            *str = "";
            delete blank;
            return false;
        }
    }
    *str = source->at(0);
    source->erase(0, 1);
    delete dummy;
    delete blank;
    return true;
}

void *noneOfNode::act(stack *values) {
    return nullptr;
}

noneOfNode *noneOfNode::copy() {
    noneOfNode *toRet = new noneOfNode();
    toRet->link = link->copy();
    return toRet;
}

noneOfNode::~noneOfNode() {
    delete link;
}

nothingNode::nothingNode() {
    id = "nothing";
}

bool nothingNode::parse(std::string *source, linkNode *path, std::string *str) {
    return false;
}

void *nothingNode::act(stack *values) {
    return nullptr;
}

nothingNode *nothingNode::copy() {
    return new nothingNode();
}

oneOrMoreNode::oneOrMoreNode() {
    id = "oneOrMore";
}

oneOrMoreNode::oneOrMoreNode(ASTNode *node) {
    populate("oneOrMore", node);
}

bool oneOrMoreNode::parse(std::string *source, linkNode *path, std::string *str) {
    std::string *blank = new std::string();
    std::string *total = new std::string();
    *blank = *str;
    bool first = true;
    do {
        if (first && link->getChild()->parse(source, path, blank)) {
            first = false;
        } else if (first) {
            *str = "";
            delete total;
            delete blank;
            return false;
        }
        *total += *blank;
    } while (link->getChild()->parse(source, path, blank));
    *str = *total;
    delete blank;
    delete total;
    return true;
}

void *oneOrMoreNode::act(stack *values) {
    return nullptr;
}

oneOrMoreNode *oneOrMoreNode::copy() {
    oneOrMoreNode *toRet = new oneOrMoreNode();
    toRet->link = link->copy();
    return toRet;
}

oneOrMoreNode::~oneOrMoreNode() {
    delete link;
}

optionalNode::optionalNode() {
    id = "optional";
}

optionalNode::optionalNode(ASTNode *node) {
    populate("optional", node);
}

bool optionalNode::parse(std::string *source, linkNode *path, std::string *str) {
    std::string *copy = new std::string();
    *copy = *str;
    if (link->getChild()->parse(source, path, copy)) {
        *str = *copy;
    }
    delete copy;
    return true;
}

void *optionalNode::act(stack *values) {
    return nullptr;
}

optionalNode *optionalNode::copy() {
    optionalNode *toRet = new optionalNode();
    toRet->link = link->copy();
    return toRet;
}

optionalNode::~optionalNode() {
    delete link;
}

peekNode::peekNode() {
    id = "peek";
}

bool peekNode::parse(std::string *source, linkNode *path, std::string *str) {
    linkNode *current = path->getTail();
    if (current->hasChild) {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    peekNode *clone = new peekNode();
    current->attach(clone);

    *str = "";
    return true;
}

void *peekNode::act(stack *values) {
    return values->peek();
}

peekNode *peekNode::copy() {
    return new peekNode();
}

popNode::popNode() {
    id = "pop";
}

bool popNode::parse(std::string *source, linkNode *path, std::string *str) {
    linkNode *current = path->getTail();
    if (current->hasChild) {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    popNode *clone = copy();
    current->attach(clone);

    *str = "";
    return true;
}

void *popNode::act(stack *values) {
    return values->pop();
}

popNode *popNode::copy() {
    return new popNode();
}

pushNode::pushNode() {
    id = "push";
}

pushNode::pushNode(std::function<void *(arg *)> func, arg *nArg) {
    id = "push";
    which = "func";
    argFunc = func;
    Arg = nArg;
    hasArgs = true;
}

pushNode::pushNode(std::function<void *()> nfunc) {
    id = "push";
    which = "func";
    func = nfunc;
    hasArgs = false;
}

pushNode::pushNode(rule *text) {
    id = "push";
    which = "match";
    match = text;
}

void *pushNode::push() {
    if (which == "func") {
        if (hasArgs) {
            return argFunc(Arg);
        }
        return func();
    }
    if (match->getNode()->getId() == "match" || match->getNode()->getId() == "pop" || match->getNode()->getId() == "peek") {
        return match->getNode()->act(temp);
    }
    return match;
}

void *pushNode::act(stack *values) {
    temp = values;
    if (which == "func" && hasArgs) {
        Arg->values = values;
    }
    values->push(push());
    return values;
}

bool pushNode::parse(std::string *source, linkNode *path, std::string *str) {
    linkNode *current = path->getTail();
    if (current->hasChild) {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    if (which == "match") {
        linkNode *dummy = new linkNode();
        std::string *empty = new std::string();
        match->getNode()->parse(empty, dummy, str);
    }

    current->attach(copy());

    *str = "";
    return true;
}

pushNode *pushNode::copy() {
    pushNode *clone = new pushNode();
    if (which == "match") {
        clone->match = match->copy();
        clone->which = "match";
        clone->hasArgs = false;
    } else if (hasArgs) {
        clone->hasArgs = true;
        clone->which = "func";
        clone->argFunc = argFunc;
        clone->Arg = Arg->copy();
    } else {
        clone->hasArgs = false;
        clone->func = func;
        clone->which = "func";
    }
    clone->temp = temp;
    return clone;
}

pushNode::~pushNode() {
    if (which == "match") {
        delete match;
    }
    if (hasArgs) {
        delete Arg;
    }
}

recursionNode::recursionNode() {
    id = "recursion";
}

recursionNode::recursionNode(std::function<rule *()> nfunc) {
    func = nfunc;
    hasArgs = false;
}

recursionNode::recursionNode(std::function<rule *(arg *)> func, arg *nArg) {
    argFunc = func;
    Arg = nArg;
    hasArgs = true;
}

bool recursionNode::parse(std::string *source, linkNode *path, std::string *str) {
    rule *eval;
    if (hasArgs) {
        eval = argFunc(Arg);
    } else {
        eval = func();
    }

    std::string *copy = new std::string();
    *copy = *str;
    bool test = eval->getNode()->parse(source, path, copy);
    if (test) {
        *str = *copy;
    } else {
        *str = "";
    }
    delete eval;
    delete copy;
    return test;
}

void *recursionNode::act(stack *values) {
    return nullptr;
}

recursionNode *recursionNode::copy() {
    recursionNode *clone = new recursionNode();
    if (hasArgs) {
        clone->Arg = Arg->copy();
        clone->argFunc = argFunc;
        clone->hasArgs = true;
    } else {
        clone->func = func;
        clone->hasArgs = false;
    }
    return clone;
}

recursionNode::~recursionNode() {
    if (hasArgs) {
        delete Arg;
    }
}

regexNode::regexNode() {
    id = "regex";
}

regexNode::regexNode(std::string nstr) {
    id = "regex";
    str = nstr;
}

bool regexNode::parse(std::string *source, linkNode *path, std::string *last) {
    try {
        std::regex rgx(str);
        std::smatch match;
        const std::string eval = *source;

        if (std::regex_search(eval.begin(), eval.end(), match, rgx) && source->find(match[1]) == 0) {
            *last = source->substr(0, match[1].length());
            source->erase(0, match[1].length());
            return true;
        }
        *last = "";
        return false;
    } catch (const std::regex_error &e) {
        std::cout << "regex_error caught: " << e.what() << std::endl;
        *last = "";
        return false;
    }
}

void *regexNode::act(stack *values) {
    return nullptr;
}

regexNode *regexNode::copy() {
    regexNode *toRet = new regexNode();
    toRet->str = str;
    return toRet;
}

sequenceNode::sequenceNode() {
    id = "sequence";
}

bool sequenceNode::parse(std::string *source, linkNode *path, std::string *str) {
    linkNode *current = link;
    linkNode *dummy = new linkNode();
    std::string *copy = new std::string;
    std::string *blank = new std::string;
    std::string *ret = new std::string;
    *blank = *str;
    *copy = *source;
    *ret = "";
    if (!current->getChild()->parse(copy, dummy, blank)) {
        delete dummy;
        delete copy;
        delete blank;
        delete ret;
        *str = "";
        return false;
    }
    *ret += *blank;
    while (current->hasSibling) {
        current = current->getSibling();
        if (!current->getChild()->parse(copy, dummy, blank)) {
            delete dummy;
            delete copy;
            delete blank;
            delete ret;
            *str = "";
            return false;
        }
        *ret += *blank;
    }

    *source = *copy;
    path->getTail()->append(dummy);
    *str = *ret;
    delete copy;
    delete blank;
    delete ret;
    return true;
}

void *sequenceNode::act(stack *values) {
    return nullptr;
}

sequenceNode *sequenceNode::copy() {
    sequenceNode *toRet = new sequenceNode();
    toRet->link = link->copy();
    return toRet;
}

sequenceNode::~sequenceNode() {
    delete link;
}

stringNode::stringNode() {
    id = "string";
}

stringNode::stringNode(std::string nstr) {
    id = "string";
    str = nstr;
}

bool stringNode::parse(std::string *source, linkNode *path, std::string *match) {
    if (source->length() == 0) {
        *match = "";
        return false;
    }
    if (source->find(str) == 0) {
        *match = source->substr(0, str.length());
        source->erase(0, str.length());
        return true;
    }
    *match = "";
    return false;
}

void *stringNode::act(stack *values) {
    return nullptr;
}

stringNode *stringNode::copy() {
    stringNode *toRet = new stringNode();
    toRet->str = str;
    return toRet;
}

swapNode::swapNode() {
    id = "swap";
}

bool swapNode::parse(std::string *source, linkNode *path, std::string *str) {
    linkNode *current = path->getTail();
    if (current->hasChild)
    {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    swapNode *clone = copy();
    current->attach(clone);

    *str = "";
    return true;
}

void *swapNode::act(stack *values) {
    values->swap();
    return nullptr;
}

swapNode *swapNode::copy() {
    return new swapNode();
}

testNode::testNode() {
    id = "test";
}

testNode::testNode(ASTNode *node) {
    populate("test", node);
}

bool testNode::parse(std::string *source, linkNode *path, std::string *str) {
    std::string *copy = new std::string;
    *copy = *source;
    linkNode *dummy = new linkNode();
    std::string *temp = new std::string;
    *temp = *str;

    if (link->getChild()->parse(copy, dummy, temp)) {
        delete dummy;
        delete temp;
        return true;
    }
    delete dummy;
    delete temp;
    return false;
}

void *testNode::act(stack *values) {
    return nullptr;
}

testNode *testNode::copy() {
    testNode *toRet = new testNode();
    toRet->link = link->copy();
    return toRet;
}

testNode::~testNode() {
    delete link;
}

testNotNode::testNotNode() {
    id = "testNot";
}

testNotNode::testNotNode(ASTNode *node) {
    populate("testNot", node);
}

bool testNotNode::parse(std::string *source, linkNode *path, std::string *str) {
    std::string *copy = new std::string;
    *copy = *source;
    linkNode *dummy = new linkNode();
    std::string *temp = new std::string;
    *temp = *str;

    if (link->getChild()->parse(copy, dummy, temp)) {
        delete dummy;
        delete temp;
        return false;
    }
    delete dummy;
    delete temp;
    return true;
}

void *testNotNode::act(stack *values) {
    return nullptr;
}

testNotNode *testNotNode::copy() {
    testNotNode *toRet = new testNotNode();
    toRet->link = link->copy();
    return toRet;
}

testNotNode::~testNotNode() {
    delete link;
}

zeroOrMoreNode::zeroOrMoreNode() {
    id = "zeroOrMore";
}

zeroOrMoreNode::zeroOrMoreNode(ASTNode *node) {
    populate("zeroOrMore", node);
}

bool zeroOrMoreNode::parse(std::string *source, linkNode *path, std::string *str) {
    std::string *blank = new std::string();
    std::string *total = new std::string();
    std::string *copy = new std::string();
    *blank = *str;
    *total = "";
    bool first = true;
    do {
        if (first && link->getChild()->parse(source, path, blank)) {
            first = false;
        } else if (first) {
            *str = "";
            delete copy;
            delete blank;
            delete total;
            return true;
        }
        *total += *blank;
    } while (link->getChild()->parse(source, path, blank));
    *str = *total;
    delete copy;
    delete blank;
    delete total;
    return true;
}

void *zeroOrMoreNode::act(stack *values) {
    return nullptr;
}

zeroOrMoreNode *zeroOrMoreNode::copy() {
    zeroOrMoreNode *toRet = new zeroOrMoreNode();
    toRet->link = link->copy();
    return toRet;
}

zeroOrMoreNode::~zeroOrMoreNode() {
    delete link;
}