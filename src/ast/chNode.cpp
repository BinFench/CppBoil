#include "ASTNode.h"

#ifndef CHNODE_CPP
#define CHNODE_CPP

class chNode: public ASTNode {
    public:
        char ch;
        chNode(char ch);
};
    
chNode::chNode(char ch) {
    id = "char";
    ch = ch;
}

#endif