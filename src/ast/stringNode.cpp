#include "ASTNode.h"
#include <string>

#ifndef STRINGNODE_CPP
#define STRINGNODE_CPP

class stringNode: public ASTNode {
    public:
        std::string str;
        stringNode(std::string str);
};
    
stringNode::stringNode(std::string str) {
    id = "string";
    str = str;
}

#endif