#include "ASTNode.h"
#include "chNode.cpp"
#include "stringNode.cpp"
#include <string>

class ignoreCaseNode: public ASTNode {
    public:
        ignoreCaseNode(char ch);
        ignoreCaseNode(chNode ch);
        ignoreCaseNode(std::string str);
        ignoreCaseNode(stringNode str);

};

ignoreCaseNode::ignoreCaseNode(char ch) {
    populate("ignoreCase", new chNode(ch));
}

ignoreCaseNode::ignoreCaseNode(chNode ch) {
    populate("ignoreCase", ch);
}

ignoreCaseNode::ignoreCaseNode(std::string str) {
    populate("ignoreCase", new stringNode(str));
}

ignoreCaseNode::ignoreCaseNode(stringNode str) {
    populate("ignoreCase", str);
}