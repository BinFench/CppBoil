#include "ASTNode.h"
#include <string>

#ifndef STRINGNODE_CPP
#define STRINGNODE_CPP

class stringNode: public ASTNode {
    public:
        std::string str;
        stringNode(std::string str);
        bool parse(std::string *source, linkNode* path);
};
    
stringNode::stringNode(std::string str) {
    id = "string";
    str = str;
}

bool stringNode::parse(std::string *source, linkNode *path) {
    if (source->find(str) == 0) {
        source->erase(0, str.length());
        return true;
    }
    return false;
}

#endif