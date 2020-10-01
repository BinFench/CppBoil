#include "ASTNode.h"
#include <string>

class regexNode: public ASTNode {
    public:
        std::string str;
        regexNode(std::string str);
};
    
regexNode::regexNode(std::string str) {
    id = "regex";
    str = str;
}