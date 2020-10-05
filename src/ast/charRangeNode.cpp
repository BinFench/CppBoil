#include "ASTNode.h"
#include "chNode.cpp"

class charRangeNode: public ASTNode {
    public:
        charRangeNode(char begin, char end);
        charRangeNode(chNode *begin, chNode *end);
};

charRangeNode::charRangeNode(char begin, char end) {
    populate("charRange", new chNode(begin), new chNode(end));
}

charRangeNode::charRangeNode(chNode *begin, chNode *end) {
    populate("charRange", begin, end);
}