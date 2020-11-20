/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: implementation of AST nodes defined in ASTNode.h
          ASTNodes implement their own rules for parsing,
          such as a sequence of other rules or one or more
          occurences of sub rules.
*/
#include "ASTNode.h"
#include "../arg.h"
#include <iostream>

//  AST: Parent node
//  Virtual constructor, unused in production.
ASTNode::ASTNode() {
    id = "AST";
}

/*  
  Base case of parametric recursion.  Populates given node with children nodes.
  type: which derived ASTNode is being populated
  node: child node to be added to parent
*/
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

/*  
  Base case of parametric recursion.  Populates given node with children nodes.
  type: which derived ASTNode is being populated
  node: string to be converted to child node
*/
void ASTNode::populate(std::string type, std::string node) {
    populate(type, new stringNode(node));
}

/*  
  Base case of parametric recursion.  Populates given node with children nodes.
  type: which derived ASTNode is being populated
  node: char to be converted to child node
*/
void ASTNode::populate(std::string type, char node) {
    populate(type, new chNode(node));
}

std::string ASTNode::getId() {
    return id;
}

void ASTNode::addChildren(linkNode *child) {
    link = child;
}

linkNode *ASTNode::getChildren() {
    return link;
}

//  any: Accepts any char if parse string is not empty

anyNode::anyNode() {
    id = "any";
}

/*
  Parse string at location 0.  anyNode accepts any character as long as it exists.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Unused here.
  str: string of last matched parse.  Is updated as the accepted character in this parse.
*/
bool anyNode::parse(std::string *source, linkNode *path, std::string *str) {
    if (source->length() > 0) {
        *str = source->at(0);
        source->erase(0, 1);
        return true;
    }
    *str = "";
    return false;
}

//  Unused implementation, exists for debug.
void *anyNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
anyNode *anyNode::copy() {
    return new anyNode;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string anyNode::prettyPrint() {
    return "[*]";
}

//  Applies simplification rules (N/A)
ASTNode *anyNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  anyOf: Accept any char if the parse string is accepted by any child node.

anyOfNode::anyOfNode() {
    id = "anyOf";
}

/*
  Parse string at location 0.  anyOfNode accepts any character as long as the
  string is matched by a child node.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Passed to child for appending.
  str: string of last matched parse.  Is updated as the accepted character in this parse.
*/
bool anyOfNode::parse(std::string *source, linkNode *path, std::string *str) {
    linkNode *current = link;
    std::string *copy = new std::string;
    *copy = *str;
    if (current->getChild()->parse(source, path, copy)) {
        *str = *copy;
        delete copy;
        return true;
    }
    
    //  If first child does not accept, traverse siblings and parse.
    while (current->hasSibling) {
        current = current->getSibling();
        if (current->getChild()->parse(source, path, copy)) {
            *str = *copy;
            delete copy;
            return true;
        }
    }

    //  No children accept, so string is rejected
    *str = "";
    delete copy;
    return false;
}

//  Unused implementation, exists for debug.
void *anyOfNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
anyOfNode *anyOfNode::copy() {
    anyOfNode *toRet = new anyOfNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string anyOfNode::prettyPrint() {
    std::string toRet = "{TEST ";
    bool first = true;
    linkNode *current = link;
    do {
        if (!first) {
            current = current->getSibling();
            toRet += " | ";
        }
        first = false;
        toRet += current->getChild()->prettyPrint();
    } while(current->hasSibling);
    toRet += " TEST}[*]";
    return toRet;
}

//  Applies simplification rules (transformation, children)
ASTNode *anyOfNode::simplify(bool *simplified) {
    //  First, simplify children before transformation 
    linkNode *current = link;
    bool childrenSimplified = true;
    bool first = true;
    bool charBased = true;
    bool *isSimplified = new bool();
    *isSimplified = false;
    do {
        if (!first) {
            current = current->getSibling();
        } else {
            first = false;
        }

        if (current->hasChild) {
            current->simplify(isSimplified);
            if (!(*isSimplified)) {
                childrenSimplified = false;
            }
        }
    } while (current->hasSibling);

    if (childrenSimplified) {
        //  Check children to see if they are char based or not
        first = true;
        current = link;
        std::string id;
        do {
            if (!first) {
                current = current->getSibling();
            } else {
                first = false;
            }

            if (current->hasChild) {
                id = current->getChild()->getId();
                if (id != "char" && id != "charRange") {
                    charBased = false;
                    break;
                }
            }
        } while (current->hasSibling);

        //  Transformation
        if (charBased) {
            //  AnyOf(...) -> firstOf(...)
            firstOfNode *parent = new firstOfNode();
            parent->addChildren(link->copy());
            return parent;
        } else {
            //  AnyOf(...) -> Sequence(Test(...), Any())
            testNode *parent = new testNode();
            parent->addChildren(link->copy());
            return new sequenceNode(parent, new anyNode());
        }
    }
    return copy();
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
anyOfNode::~anyOfNode() {
    delete link;
}

//  charRange: Accepts any char if it exists in the range defined by children nodes.

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

/*
  Parse string at location 0.  charRangeNode accepts any char as it fits the range.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Unused here.
  str: string of last matched parse.  Is updated as the accepted character in this parse.
*/
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

//  Unused implementation, exists for debug.
void *charRangeNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
charRangeNode *charRangeNode::copy() {
    charRangeNode *toRet = new charRangeNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string charRangeNode::prettyPrint() {
    std::string toRet = "[";
    toRet += link->getChild()->prettyPrint();
    toRet += "-";
    toRet += link->getSibling()->getChild()->prettyPrint();
    toRet += "]";
    return toRet;
}

//  Applies simplification rules (N/A)
ASTNode *charRangeNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
charRangeNode::~charRangeNode() {
    delete link;
}

// Ch: Accept only a matching char.

chNode::chNode() {
    id = "char";
    ch = '\0';
}

chNode::chNode(char nch) {
    id = "char";
    ch = nch;
}

/*
  Parse string at location 0.  chNode accepts only a matching char.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Unused here.
  str: string of last matched parse.  Is updated as the accepted character in this parse.
*/
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

//  Unused implementation, exists for debug.
void *chNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
chNode *chNode::copy() {
    chNode *toRet = new chNode();
    toRet->ch = ch;
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string chNode::prettyPrint() {
    std::string toRet = "[";
    if (ch == '[' || ch == '{' || ch == '}' || ch == ']') {
        toRet += "'";
        toRet += ch;
        toRet += "']";
        return toRet;
    }
    toRet += ch;
    toRet += "]";
    return toRet;
}

//  Applies simplification rules (N/A)
ASTNode *chNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  empty: Matches anything, does not cut parse string

emptyNode::emptyNode() {
    id = "empty";
}

/*
  Parse string at location 0.  emptyNode always accepts.
  Return true always
  source: string to be parsed.  May be substring of parent node.  Unused here
  path: linked list of stack actions for tokenizing input.  Unused here.
  str: string of last matched parse.  Is cleared here.
*/
bool emptyNode::parse(std::string *source, linkNode *path, std::string *str) {
    *str = "";
    return true;
}

//  Unused implementation, exists for debug.
void *emptyNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
emptyNode *emptyNode::copy() {
    return new emptyNode();
}

//  Dedicated pretty print to convert to Production Rule Form
std::string emptyNode::prettyPrint() {
    return "{SIGMA}";
}

//  Applies simplification rules (N/A)
ASTNode *emptyNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  EOI: Only matches end of input (empty parse string)

EOINode::EOINode() {
    id = "EOI";
}

/*
  Parse string at location 0.  EOINode accepts only a matching char.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.  Unused here
  path: linked list of stack actions for tokenizing input.  Unused here.
  str: string of last matched parse.  Is cleared here.
*/
bool EOINode::parse(std::string *source, linkNode *path, std::string *str) {
    if (source->length() == 0) {
        *str = "";
        return true;
    }
    *str = "";
    return false;
}

//  Unused implementation, exists for debug.
void *EOINode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
EOINode *EOINode::copy() {
    return new EOINode();
}

//  Dedicated pretty print to convert to Production Rule Form
std::string EOINode::prettyPrint() {
    return "{EOI}";
}

//  Applies simplification rules (N/A)
ASTNode *EOINode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

// firstOf: Matches the first rule that accepts the parse string

firstOfNode::firstOfNode() {
    id = "firstOf";
}

/*
  Parse string at location 0.  firstOfNode accepts any string as long as the
  string is matched by a child node.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Passed to child for appending.
  str: string of last matched parse.  Is updated as the accepted string in this parse.
*/
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

//  Unused implementation, exists for debug.
void *firstOfNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
firstOfNode *firstOfNode::copy() {
    firstOfNode *toRet = new firstOfNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string firstOfNode::prettyPrint() {
    std::string toRet = "{SCAN ";
    bool first = true;
    linkNode *current = link;

    do {
        if (!first) {
            current = current->getSibling();
            toRet += " SCAN} | {SCAN ";
        }
        first = false;
        toRet += current->getChild()->prettyPrint();
    } while(current->hasSibling);
    toRet += " SCAN}";
    return toRet;
}

//  Applies simplification rules (transformation, children)
ASTNode *firstOfNode::simplify(bool *simplified) {
    return this;
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
firstOfNode::~firstOfNode() {
    delete link;
}

/*
    ignoreCase: Matches any char or string as long as it is accepted by the child
    while ignoring capitalization.
*/

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

/*
  Parse string at location 0.  firstOfNode accepts any string as long as the
  string is matched by a child node ignoring capitalization.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Passed to child for appending.
  str: string of last matched parse.  Is updated as the accepted string in this parse.
*/
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
        //  Convert the source string and node string to lowercase to compare.
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

//  Unused implementation, exists for debug.
void *ignoreCaseNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
ignoreCaseNode *ignoreCaseNode::copy() {
    ignoreCaseNode *toRet = new ignoreCaseNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string ignoreCaseNode::prettyPrint() {
    std::string toRet = "^[";
    toRet += link->getChild()->prettyPrint();
    toRet += "]";
    return toRet;
}

//  Applies simplification rules (N/A)
ASTNode *ignoreCaseNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
ignoreCaseNode::~ignoreCaseNode() {
    delete link;
}

// match: a stack action node.  Stores the last matched parse string.

matchNode::matchNode() {
    id = "match";
}

/*
  matchNode always passes parse, stores last matched parse for stack.
  Always returns true.
  source: string to be parsed.  May be substring of parent node.  Unused here.
  path: linked list of stack actions for tokenizing input.  Copy of node appended.
  str: string of last matched parse.  Is stored and cleared.
*/
bool matchNode::parse(std::string *source, linkNode *path, std::string *str) {
    match = *str;
    linkNode *current = path->getTail();
    if (current->hasChild) {
        linkNode *next = new linkNode();
        current->append(next);
        current = next;
    }
    //  Because the parser deletes the parsed rule and the stack actions, a copy
    //  is needed so that there is no double free error.
    matchNode *clone = copy();
    current->attach(clone);

    *str = "";
    return true;
}

// Return the stored matched parse as void pointer.
void *matchNode::act(stack *values) {
    std::string *toRet = new std::string();
    *toRet = match;
    return static_cast<void *>(toRet);
}

//  Dedicated copy function for memory management.
matchNode *matchNode::copy() {
    matchNode *toRet = new matchNode();
    toRet->match = match;
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string matchNode::prettyPrint() {
    return "{MATCH}";
}

//  Applies simplification rules (N/A)
ASTNode *matchNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  noneOf:  Accepts any char as long as the parse string does not match any child rules.

noneOfNode::noneOfNode() {
    id = "noneOf";
}

/*
  Parse string at location 0.  noneOfNode accepts any character as long as the
  string is not matched by any child node.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Unused here.
  str: string of last matched parse.  Is updated as the accepted character in this parse.
*/
bool noneOfNode::parse(std::string *source, linkNode *path, std::string *str) {
    //  We copy all parameters as we don't want the child nodes to update parse state.
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
        delete sample;
        return false;
    }

    //  If first child doesn't match, we traverse siblings.
    while (current->hasSibling) {
        current = current->getSibling();
        *sample = *source;
        if (current->getChild()->parse(sample, dummy, blank)) {
            delete dummy;
            *str = "";
            delete blank;
            delete sample;
            return false;
        }
    }

    //  None of the children match, so a char can be accepted.
    *str = source->at(0);
    source->erase(0, 1);
    delete dummy;
    delete blank;
    delete sample;
    return true;
}

//  Unused implementation, exists for debug.
void *noneOfNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
noneOfNode *noneOfNode::copy() {
    noneOfNode *toRet = new noneOfNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string noneOfNode::prettyPrint() {
    std::string toRet = "{TESTNOT ";
    bool first = true;
    linkNode *current = link;
    do {
        if (!first) {
            current = current->getSibling();
            toRet += " | ";
        }
        first = false;
        toRet += current->getChild()->prettyPrint();
    } while(current->hasSibling);
    toRet += " TESTNOT}[*]";
    return toRet;
}

//  Applies simplification rules (transformation)
ASTNode *noneOfNode::simplify(bool *simplified) {
    //  First, simplify children before transformation 
    linkNode *current = link;
    bool childrenSimplified = true;
    bool first = true;
    bool charBased = true;
    bool *isSimplified = new bool();
    *isSimplified = false;
    do {
        if (!first) {
            current = current->getSibling();
        } else {
            first = false;
        }

        if (current->hasChild) {
            current->simplify(isSimplified);
            if (!(*isSimplified)) {
                childrenSimplified = false;
            }
        }
    } while (current->hasSibling);

    if (childrenSimplified) {
        //  Check children to see if they are char based or not
        first = true;
        current = link;
        std::string id;
        do {
            if (!first) {
                current = current->getSibling();
            } else {
                first = false;
            }

            if (current->hasChild) {
                id = current->getChild()->getId();
                if (id != "char" && id != "charRange") {
                    charBased = false;
                    break;
                }
            }
        } while (current->hasSibling);

        //  Transformation
        if (charBased) {
            //  noneOf(...) -> Sequence(testNot(firstOf(...)), Any())
            firstOfNode *parent = new firstOfNode();
            parent->addChildren(link->copy());
            return new sequenceNode(new testNotNode(parent), new anyNode());
        } else {
            //  noneOf(...) -> Sequence(testNot(...), Any())
            testNotNode *parent = new testNotNode();
            parent->addChildren(link->copy());
            return new sequenceNode(parent, new anyNode());
        }
    }
    return copy();
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
noneOfNode::~noneOfNode() {
    delete link;
}

//  nothing:  Accepts nothing.

nothingNode::nothingNode() {
    id = "nothing";
}

// No used parameters, never accepts.
bool nothingNode::parse(std::string *source, linkNode *path, std::string *str) {
    return false;
}

//  Unused implementation, exists for debug.
void *nothingNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
nothingNode *nothingNode::copy() {
    return new nothingNode();
}

//  Dedicated pretty print to convert to Production Rule Form
std::string nothingNode::prettyPrint() {
    return "{FAIL}";
}

//  Applies simplification rules (N/A)
ASTNode *nothingNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

/*
  oneOrMore: This rule matches multiple occurances of its sub rules.
  At least one occurance must match for parse to accept.
*/

oneOrMoreNode::oneOrMoreNode() {
    id = "oneOrMore";
}

oneOrMoreNode::oneOrMoreNode(ASTNode *node) {
    populate("oneOrMore", node);
}

/*
  Parse string at location 0.  oneOrMoreNode accepts each occurance of the subrules.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Passed to child for appending.
  str: string of last matched parse.  Is updated as the accepted total string in this parse.
*/
bool oneOrMoreNode::parse(std::string *source, linkNode *path, std::string *str) {
    //  A copy of the match string is made since the final match is a sum of all child matches.
    std::string *blank = new std::string();
    std::string *total = new std::string();
    *blank = *str;
    bool first = true;
    do {
        //  Parse only fails if child parse fails the first time.
        if (first && link->getChild()->parse(source, path, blank)) {
            first = false;
        } else if (first) {
            *str = "";
            delete total;
            delete blank;
            return false;
        }
        *total += *blank;
        //  Parsing repeats until it fails, and total parsing accepts.
    } while (link->getChild()->parse(source, path, blank));
    *str = *total;
    delete blank;
    delete total;
    return true;
}

//  Unused implementation, exists for debug.
void *oneOrMoreNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
oneOrMoreNode *oneOrMoreNode::copy() {
    oneOrMoreNode *toRet = new oneOrMoreNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string oneOrMoreNode::prettyPrint() {
    std::string toRet = "[";
    toRet += link->getChild()->prettyPrint();
    toRet += "]+";
    return toRet;
}

//  Applies simplification rules (children)
ASTNode *oneOrMoreNode::simplify(bool *simplified) {
    return this;
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
oneOrMoreNode::~oneOrMoreNode() {
    delete link;
}

//  optional:  Will pass no matter what, though can optionally parse based on subrule.

optionalNode::optionalNode() {
    id = "optional";
}

optionalNode::optionalNode(ASTNode *node) {
    populate("optional", node);
}

/*
  Parse string at location 0.  optionalNode optionally accepts subrule.
  Return true no matter what
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Passed to child for appending.
  str: string of last matched parse.  Is updated as the accepted string in this parse.
*/
bool optionalNode::parse(std::string *source, linkNode *path, std::string *str) {
    std::string *copy = new std::string();
    *copy = *str;
    if (link->getChild()->parse(source, path, copy)) {
        *str = *copy;
    }
    delete copy;
    return true;
}

//  Unused implementation, exists for debug.
void *optionalNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
optionalNode *optionalNode::copy() {
    optionalNode *toRet = new optionalNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string optionalNode::prettyPrint() {
    std::string toRet = "[";
    toRet += link->getChild()->prettyPrint();
    toRet += "]?";
    return toRet;
}

//  Applies simplification rules (transformation)
ASTNode *optionalNode::simplify(bool *simplified) {
    return new firstOfNode(link->getChild()->copy(), new emptyNode());
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
optionalNode::~optionalNode() {
    delete link;
}

//  peek: Stack action gives reference to item on top of stack.

peekNode::peekNode() {
    id = "peek";
}

//  Parse always passes, appends copy of node to linked list.
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

//  Returns reference to item at top of stack.
void *peekNode::act(stack *values) {
    return values->peek();
}

//  Dedicated copy function for memory management.
peekNode *peekNode::copy() {
    return new peekNode();
}

//  Dedicated pretty print to convert to Production Rule Form
std::string peekNode::prettyPrint() {
    return "{PEEK}";
}

//  Applies simplification rules (N/A)
ASTNode *peekNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  pop:  Stack action returns item from top of stack.

popNode::popNode() {
    id = "pop";
}

//  Parse always passes, appends copy of node to linked list
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

//  Return item from top of stack.
void *popNode::act(stack *values) {
    return values->pop();
}

//  Dedicated copy function for memory management.
popNode *popNode::copy() {
    return new popNode();
}

//  Dedicated pretty print to convert to Production Rule Form
std::string popNode::prettyPrint() {
    return "{POP}";
}

//  Applies simplification rules (N/A)
ASTNode *popNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  push: Stack action pushes item to top of stack.

pushNode::pushNode() {
    id = "push";
    hasArgs = false;
    which = "";
}

/*
  Because a given item can be pushed multiple times, the constructor recieves
  a function with or without arguments that constructs an object to push.
*/

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
    hasArgs = false;
    match = text;
}

//  Returns the item to be pushed to the stack.
void *pushNode::push() {
    if (which == "func") {
        if (hasArgs) {
            return argFunc(Arg);
        }
        return func();
    }
    //  If the item is a match, pop, or peek node, apply stack actions to be pushed.
    if (match->getNode()->getId() == "match" || match->getNode()->getId() == "pop" || match->getNode()->getId() == "peek") {
        void *res = match->getNode()->act(temp);
        return res;
    }
    rule *res = match->copy();
    return res;
}

// Push stored item to stack.
void *pushNode::act(stack *values) {
    temp = values;
    if (which == "func" && hasArgs) {
        Arg->values = values;
    }
    values->push(push());
    return values;
}

//  Parse always passes, updates child node if needed, appends copy to linked list.
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
        delete empty;
        delete dummy;
    }

    current->attach(copy());

    *str = "";
    return true;
}

//  Dedicated copy function for memory management.
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

//  Dedicated pretty print to convert to Production Rule Form
std::string pushNode::prettyPrint() {
    return "{PUSH}";
}

//  Applies simplification rules (N/A)
ASTNode *pushNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  Destructor: Node may have child or args to be cleaned.
pushNode::~pushNode() {
    if (which == "match") {
        delete match->getNode();
        delete match;
    }
    if (hasArgs) {
        delete Arg;
    }
}

/*
  recursion: used to call a parent rule without an infinite loop.  Rule is not
  constructed until it needs to be evaluated for parsing.
*/

recursionNode::recursionNode() {
    id = "recursion";
}

//  In case parent rule takes arguments, there is the option to pass args.

recursionNode::recursionNode(std::function<rule *()> nfunc) {
    func = nfunc;
    hasArgs = false;
}

recursionNode::recursionNode(int numid, std::function<rule *()> nfunc) {
    func = nfunc;
    hasArgs = false;
    rid = numid;
}

recursionNode::recursionNode(std::function<rule *(arg *)> func, arg *nArg) {
    argFunc = func;
    Arg = nArg;
    hasArgs = true;
}

recursionNode::recursionNode(int numid, std::function<rule *(arg *)> func, arg *nArg) {
    argFunc = func;
    Arg = nArg;
    hasArgs = true;
    rid = numid;
}

/*
  Parse string at location 0.  recursionNode parses with parent rule.
  Return true if parse accepts, false otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Passed to child for appending.
  str: string of last matched parse.  Is updated as the accepted string in this parse.
*/
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
    delete eval->getNode();
    delete eval;
    delete copy;
    return test;
}

//  Unused implementation, exists for debug.
void *recursionNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
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

//  Dedicated pretty print to convert to Production Rule Form
std::string recursionNode::prettyPrint() {
    //  TODO: Determine rule being recursed
    return "{R}";
}

//  Applies simplification rules (N/A)
ASTNode *recursionNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  Destructor: Node may have args to be cleaned.
recursionNode::~recursionNode() {
    if (hasArgs) {
        delete Arg;
    }
}

//  regex: parses string based on regex.

regexNode::regexNode() {
    id = "regex";
}

regexNode::regexNode(std::string nstr) {
    id = "regex";
    str = nstr;
}

/*
  Parse string at location 0.  regexNode parses with regex from constructor.
  Return true if parse accepts, false otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Not used here.
  last: string of last matched parse.  Is updated as the accepted string in this parse.
*/
bool regexNode::parse(std::string *source, linkNode *path, std::string *last) {
    try {
        std::regex rgx(str);
        std::smatch match;
        const std::string eval = *source;

        // Test string on regex, update last match on regex success.
        if (std::regex_search(eval.begin(), eval.end(), match, rgx) && source->find(match[1]) == 0) {
            *last = source->substr(0, match[1].length());
            source->erase(0, match[1].length());
            return true;
        }
        *last = "";
        return false;
    } catch (const std::regex_error &e) {
        //  error with defined regex
        std::cout << "regex_error caught: " << e.what() << std::endl;
        *last = "";
        return false;
    }
}

//  Unused implementation, exists for debug.
void *regexNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
regexNode *regexNode::copy() {
    regexNode *toRet = new regexNode();
    toRet->str = str;
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string regexNode::prettyPrint() {
    std::string toRet = "[\\";
    toRet += str;
    toRet += "]";
    return toRet;
}

//  Applies simplification rules (N/A)
ASTNode *regexNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  rule: Contains subnodes as Production Rule.

ruleNode::ruleNode() {
    id = "rule";
}

ruleNode::ruleNode(ASTNode *child, bool def) {
    isDef = def;
    populate("rule", child);
}

// Get if this Production Rule is nullable
bool ruleNode::getNull() {
    return false;
}

// Get the first set of this Production Rule
void *ruleNode::getFirst() {
    return nullptr;
}

// Get the follow set of this Production Rule
void *ruleNode::getFollow() {
    return nullptr;
}

// Get the predict set of this Production Rule
void *ruleNode::getPredict() {
    return nullptr;
}

/*
  Parse string at location 0.  ruleNode parses with children.
  Return true if parse accepts, false otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Passed to children.
  last: string of last matched parse.  Is updated as the accepted string in this parse.
*/
bool ruleNode::parse(std::string *source, linkNode *path, std::string *last) {
    std::string *copy = new std::string();
    *copy = *last;
    if (link->getChild()->parse(source, path, copy)) {
        *last = *copy;
        delete copy;
        return true;
    }
    delete copy;
    return false;
}

//  Unused implementation, exists for debug.
void *ruleNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
ruleNode *ruleNode::copy() {
    ruleNode *toRet = new ruleNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string ruleNode::prettyPrint() {
    return link->getChild()->prettyPrint();
}

//  Applies simplification rules (children)
ASTNode *ruleNode::simplify(bool *simplified) {
    return this;
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
ruleNode::~ruleNode() {
    delete link;
}

//  sequence: parses based on multiple sub rules in a sequence.

sequenceNode::sequenceNode() {
    id = "sequence";
}

/*
  Parse string at location 0.  sequenceNode parses with each child node.
  Return true if parse accepts, false otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Passed to child for appending.
  last: string of last matched parse.  Is updated as the total accepted string in this parse.
*/
bool sequenceNode::parse(std::string *source, linkNode *path, std::string *str) {
    linkNode *current = link;
    //  All parameters are copied
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
    //  Append sub match to total match
    *ret += *blank;
    //  Traverse siblings if first node matched
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
    //  Append child link list to parameter link list
    path->getTail()->append(dummy);
    *str = *ret;
    delete copy;
    delete blank;
    delete ret;
    return true;
}

//  Unused implementation, exists for debug.
void *sequenceNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
sequenceNode *sequenceNode::copy() {
    sequenceNode *toRet = new sequenceNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string sequenceNode::prettyPrint() {
    std::string toRet = "[";
    bool first = true;
    linkNode *current = link;
    do {
        if (!first) {
            current = current->getSibling();
            toRet += ", ";
        }
        first = false;
        toRet += current->getChild()->prettyPrint();
    } while(current->hasSibling);
    toRet += "]";
    return toRet;
}

//  Applies simplification rules (transform, children)
ASTNode *sequenceNode::simplify(bool *simplified) {
    if (!link->isSimplified) {
        linkNode *newLink = link->mergeSequenceGrandchildren(simplified);
        delete link;
        link = newLink;
    }
    return copy();
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
sequenceNode::~sequenceNode() {
    delete link;
}

//  string: parses string if it matches string in node.

stringNode::stringNode() {
    id = "string";
}

stringNode::stringNode(std::string nstr) {
    id = "string";
    str = nstr;
}

/*
  Parse string at location 0.  stringNode accepts only a matching string.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Unused here.
  str: string of last matched parse.  Is updated as the accepted string in this parse.
*/
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

//  Unused implementation, exists for debug.
void *stringNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
stringNode *stringNode::copy() {
    stringNode *toRet = new stringNode();
    toRet->str = str;
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string stringNode::prettyPrint() {
    std::string toRet = "[";
    toRet += str;
    toRet += "]";
    return toRet;
}

//  Applies simplification rules (transformation)
ASTNode *stringNode::simplify(bool *simplified) {
    return this;
}

//  swap: Stack action that swaps the top of the stack with the node below it.

swapNode::swapNode() {
    id = "swap";
}

//  Parse always accepts, append copy of node to link list.
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

//  Swap top two items on stack
void *swapNode::act(stack *values) {
    values->swap();
    return values;
}

//  Dedicated copy function for memory management.
swapNode *swapNode::copy() {
    return new swapNode();
}

//  Dedicated pretty print to convert to Production Rule Form
std::string swapNode::prettyPrint() {
    return "{SWAP}";
}

//  Applies simplification rules (N/A)
ASTNode *swapNode::simplify(bool *simplified) {
    *simplified = true;
    return copy();
}

//  test: Parses string based on sub rule but will not update parse state.

testNode::testNode() {
    id = "test";
}

testNode::testNode(ASTNode *node) {
    populate("test", node);
}

/*
  Parse string at location 0.  testNode accepts only if subrule accepts.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Unused here.
  str: string of last matched parse.  Unused here.
*/
bool testNode::parse(std::string *source, linkNode *path, std::string *str) {
    //  All parameters copied so as not to be updated by child.
    std::string *copy = new std::string;
    *copy = *source;
    linkNode *dummy = new linkNode();
    std::string *temp = new std::string;
    *temp = *str;

    if (link->getChild()->parse(copy, dummy, temp)) {
        delete dummy;
        delete temp;
        delete copy;
        return true;
    }
    delete dummy;
    delete temp;
    delete copy;
    return false;
}

//  Unused implementation, exists for debug.
void *testNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
testNode *testNode::copy() {
    testNode *toRet = new testNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string testNode::prettyPrint() {
    std::string toRet = "{TEST ";
    toRet += link->getChild()->prettyPrint();
    toRet += " TEST}";
    return toRet;
}

//  Applies simplification rules (children)
ASTNode *testNode::simplify(bool *simplified) {
    return this;
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
testNode::~testNode() {
    delete link;
}

/*
  testNot: Parses string based on sub rule but will not update parse state.
  Opposite of test, this passes if subrule does not pass.
*/
testNotNode::testNotNode() {
    id = "testNot";
}

testNotNode::testNotNode(ASTNode *node) {
    populate("testNot", node);
}

/*
  Parse string at location 0.  testNode accepts only if subrule rejects.
  Return true if string is accepted.  False otherwise
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Unused here.
  str: string of last matched parse.  Unused here.
*/
bool testNotNode::parse(std::string *source, linkNode *path, std::string *str) {
    //  All parameters are copied so as not to be updated by child.
    std::string *copy = new std::string;
    *copy = *source;
    linkNode *dummy = new linkNode();
    std::string *temp = new std::string;
    *temp = *str;

    if (link->getChild()->parse(copy, dummy, temp)) {
        delete dummy;
        delete temp;
        delete copy;
        return false;
    }
    delete dummy;
    delete temp;
    delete copy;
    return true;
}

//  Unused implementation, exists for debug.
void *testNotNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
testNotNode *testNotNode::copy() {
    testNotNode *toRet = new testNotNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string testNotNode::prettyPrint() {
    std::string toRet = "{TESTNOT ";
    toRet += link->getChild()->prettyPrint();
    toRet += " TESTNOT}";
    return toRet;
}

//  Applies simplification rules (children)
ASTNode *testNotNode::simplify(bool *simplified) {
    return this;
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
testNotNode::~testNotNode() {
    delete link;
}

/*
  zeroOrMode: This rule matches multiple occurances of its sub rules.
  This rule accepts no matter what.  No occurance necessary. 
*/

zeroOrMoreNode::zeroOrMoreNode() {
    id = "zeroOrMore";
}

zeroOrMoreNode::zeroOrMoreNode(ASTNode *node) {
    populate("zeroOrMore", node);
}

/*
  Parse string at location 0.  zeroOrMoreNode accepts each occurance of the subrules.
  Return true no matter what.
  source: string to be parsed.  May be substring of parent node.
  path: linked list of stack actions for tokenizing input.  Passed to child for appending.
  str: string of last matched parse.  Is updated as the accepted total string in this parse.
*/
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
        //  Append sub match to total match.
        *total += *blank;
        //  Continue parsing until parsing fails.
    } while (link->getChild()->parse(source, path, blank));
    *str = *total;
    delete copy;
    delete blank;
    delete total;
    return true;
}

//  Unused implementation, exists for debug.
void *zeroOrMoreNode::act(stack *values) {
    return values;
}

//  Dedicated copy function for memory management.
zeroOrMoreNode *zeroOrMoreNode::copy() {
    zeroOrMoreNode *toRet = new zeroOrMoreNode();
    toRet->link = link->copy();
    return toRet;
}

//  Dedicated pretty print to convert to Production Rule Form
std::string zeroOrMoreNode::prettyPrint() {
    std::string toRet = "[";
    toRet += link->getChild()->prettyPrint();
    toRet += "]*";
    return toRet;
}

//  Applies simplification rules (transformation)
ASTNode *zeroOrMoreNode::simplify(bool *simplified) {
    return new firstOfNode(new oneOrMoreNode(link->getChild()->copy()), new emptyNode());
}

//  Destructor: Because this has child nodes, those need to be cleaned up.
zeroOrMoreNode::~zeroOrMoreNode() {
    delete link;
}