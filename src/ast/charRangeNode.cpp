#include "ASTNode.h"
#include "chNode.cpp"
#include <algorithm>

class charRangeNode: public ASTNode {
    public:
        charRangeNode(char begin, char end);
        charRangeNode(chNode *begin, chNode *end);
        bool parse(std::string *source, linkNode* path);
};

charRangeNode::charRangeNode(char begin, char end) {
    populate("charRange", new chNode(begin), new chNode(end));
}

charRangeNode::charRangeNode(chNode *begin, chNode *end) {
    populate("charRange", begin, end);
}

bool charRangeNode::parse(std::string *source, linkNode *path) {
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
        source->erase(0, 1);
        return true;
    }
    return false;
}