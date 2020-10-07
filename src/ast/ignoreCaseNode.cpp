#include "ASTNode.h"
#include "chNode.cpp"
#include "stringNode.cpp"
#include <string>
#include <algorithm>

class ignoreCaseNode: public ASTNode {
    public:
        ignoreCaseNode(char ch);
        ignoreCaseNode(chNode *ch);
        ignoreCaseNode(std::string str);
        ignoreCaseNode(stringNode *str);
        bool parse(std::string *source, linkNode* path);
};

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

bool ignoreCaseNode::parse(std::string *source, linkNode* path) {
    if (link->getChild()->getId() == "char") {
        if (tolower(source->at(0)) == tolower(((chNode *)link->getChild())->ch)) {
            source->erase(0, 1);
            return true;
        }
        return false;
    } else {
        std::string data = ((stringNode *)link->getChild())->str;
        std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return tolower(c); });

        std::string data2 = source->substr(0, data.length());
        std::transform(data2.begin(), data2.end(), data2.begin(),
        [](unsigned char c){ return tolower(c); });

        if (data == data2) {
            source->erase(0, data.length());
            return true;
        }
        return false;
    }
}