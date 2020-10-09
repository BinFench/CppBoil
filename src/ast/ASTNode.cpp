#include "ASTNode.h"

template <typename... Args>
void ASTNode::populate(std::string type, ASTNode *node, Args... nodes)
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
    populate(type, nodes...);
}

template <typename... Args>
void ASTNode::populate(std::string type, std::string node, Args... nodes)
{
    if (id != type)
    {
        id = type;
        link = new linkNode();
        link->attach(new stringNode(node));
    }
    else
    {
        linkNode *sibling = new linkNode();
        sibling->attach(new stringNode(node));
        link->getTail()->append(sibling);
    }
    populate(type, nodes...);
}

template <typename... Args>
void ASTNode::populate(std::string type, char node, Args... nodes)
{
    if (id != type)
    {
        id = type;
        link = new linkNode();
        link->attach(new chNode(node));
    }
    else
    {
        linkNode *sibling = new linkNode();
        sibling->attach(new chNode(node));
        link->getTail()->append(sibling);
    }
    populate(type, nodes...);
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
        link->append(sibling);
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
    return false;
}

template <typename... Args>
anyOfNode::anyOfNode(Args... nodes)
{
    populate("anyOf", nodes...);
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
    return false;
}

charRangeNode::charRangeNode(char begin, char end)
{
    populate("charRange", new chNode(begin), new chNode(end));
}

charRangeNode::charRangeNode(chNode *begin, chNode *end)
{
    populate("charRange", begin, end);
}

bool charRangeNode::parse(std::string *source, linkNode *path, std::string *str)
{
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

    if (temp >= min && temp <= max)
    {
        *str += source->at(0);
        source->erase(0, 1);
        return true;
    }
    return false;
}

chNode::chNode(char ch)
{
    id = "char";
    ch = ch;
}

bool chNode::parse(std::string *source, linkNode *path, std::string *str)
{
    if (source->at(0) == ch)
    {
        *str += source->at(0);
        source->erase(0, 1);
        return true;
    }
    return false;
}

emptyNode::emptyNode()
{
    id = "empty";
}

bool emptyNode::parse(std::string *source, linkNode *path, std::string str)
{
    return true;
}

EOINode::EOINode()
{
    id = "EOI";
}

bool EOINode::parse(std::string *source, linkNode *path, std::string str)
{
    return (source->length() == 0);
}

template <typename... Args>
firstOfNode::firstOfNode(Args... nodes)
{
    populate("firstOf", nodes...);
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
    return false;
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
    if (link->getChild()->getId() == "char")
    {
        if (tolower(source->at(0)) == tolower(((chNode *)link->getChild())->ch))
        {
            *str += source->at(0);
            source->erase(0, 1);
            return true;
        }
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
        return false;
    }
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

template <typename... Args>
noneOfNode::noneOfNode(Args... nodes)
{
    populate("noneOf", nodes...);
}

bool noneOfNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string *blank;
    *blank = *str;
    linkNode *dummy = new linkNode();
    linkNode *current = link;
    std::string sample = *source;
    if (current->getChild()->parse(&sample, dummy, blank))
    {
        delete dummy;
        return false;
    }
    while (current->hasSibling)
    {
        current = current->getSibling();
        sample = *source;
        if (current->getChild()->parse(&sample, dummy, blank))
        {
            delete dummy;
            return false;
        }
    }
    *str += source->at(0);
    source->erase(0, 1);
    delete dummy;
    return true;
}

nothingNode::nothingNode()
{
    id = "nothing";
}

bool nothingNode::parse(std::string *source, linkNode *path, std::string *str)
{
    return false;
}

oneOrMoreNode::oneOrMoreNode(ASTNode *node)
{
    populate("oneOrMore", node);
}

bool oneOrMoreNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string *blank;
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
            return false;
        }
    } while (link->getChild()->parse(source, path, blank));
    *str += *blank;
    return true;
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

pushNode::pushNode(std::function<void *(arg *)> func, arg *Arg)
{
    id = "push";
    which = "func";
    argFunc = func;
    Arg = Arg;
    hasArgs = true;
}

template <typename... Args>
pushNode::pushNode(std::function<void *(arg *)> func, Args... Arg)
{
    pushNode(func, new arg(Arg...));
}

pushNode::pushNode(std::function<void *()> func)
{
    id = "push";
    which = "func";
    func = func;
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
        std::string *empty;
        match->getNode()->parse(empty, dummy, str);
    }

    return true;
}

recursionNode::recursionNode(std::function<rule *()> func)
{
    func = func;
    hasArgs = false;
}

recursionNode::recursionNode(std::function<rule *(arg *)> func, arg *Arg)
{
    argFunc = func;
    Arg = Arg;
    hasArgs = true;
}

template <typename... Args>
recursionNode::recursionNode(std::function<rule *(arg *)> func, Args... Arg)
{
    recursionNode(func, new arg(Arg...));
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

regexNode::regexNode(std::string str)
{
    id = "regex";
    str = str;
}

bool regexNode::parse(std::string *source, linkNode *path, std::string *last)
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
    return false;
}

template <typename... Args>
sequenceNode::sequenceNode(Args... nodes)
{
    populate("sequence", nodes...);
}

bool sequenceNode::parse(std::string *source, linkNode *path, std::string *str)
{
    linkNode *current = link;
    std::string copy = *source;
    linkNode *dummy = new linkNode();
    std::string *blank;
    std::string *temp;
    std::string *ret;
    *blank = *str;
    if (!current->getChild()->parse(&copy, dummy, blank))
    {
        delete dummy;
        return false;
    }
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
            return false;
        }
        *blank = blank->substr(temp->length(), (blank->length() - temp->length()));
        *ret += *blank;
    }

    source = &copy;
    path->getTail()->append(dummy);
    *str = *ret;
    return true;
}

stringNode::stringNode(std::string str)
{
    id = "string";
    str = str;
}

bool stringNode::parse(std::string *source, linkNode *path, std::string *match)
{
    if (source->find(str) == 0)
    {
        *match += source->substr(0, str.length());
        source->erase(0, str.length());
        return true;
    }
    return false;
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
    std::string *temp;
    *temp = *str;

    if (link->getChild()->parse(&copy, dummy, temp))
    {
        delete dummy;
        return true;
    }
    delete dummy;
    return false;
}

testNotNode::testNotNode(ASTNode *node)
{
    populate("testNot", node);
}

bool testNotNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string copy = *source;
    linkNode *dummy = new linkNode();
    std::string *temp;
    *temp = *str;

    if (link->getChild()->parse(&copy, dummy, temp))
    {
        delete dummy;
        return false;
    }
    delete dummy;
    return true;
}

zeroOrMoreNode::zeroOrMoreNode(ASTNode *node)
{
    populate("zeroOrMore", node);
}

bool zeroOrMoreNode::parse(std::string *source, linkNode *path, std::string *str)
{
    std::string *blank;
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