#include "ASTNode.h"

#ifndef CHNODE_CPP
#define CHNODE_CPP

class chNode: public ASTNode {
    public:
        char ch;
        chNode(char ch);
        bool parse(std::string *source, linkNode* path);
};
    
chNode::chNode(char ch) {
    id = "char";
    ch = ch;
}

bool chNode::parse(std::string *source, linkNode *path) {
    if (source->at(0) == ch) {
        source->erase(0, 1);
        return true;
    }
    return false;
}

#endif