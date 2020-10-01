#include "ASTNode.h"

class chNode: public ASTNode {
    public:
        char ch;
        chNode(char ch);
};
    
chNode::chNode(char ch) {
    id = "char";
    ch = ch;
}