#include "ASTNode.h"
#include "stringNode.cpp"
#include "chNode.cpp"
#include <type_traits>

template<typename T, typename... Args>
void ASTNode::populate(std::string type, T *node, Args... nodes) {
    if (id != type) {
        id = type;
        link = new linkNode();
        if (std::is_same<T, ASTNode>::value) {
            link->attach(node);
        } else if (std::is_same<T, std::string>::value) {
            link->attach(new stringNode(node))
        } else if (std::is_same<T, char>::value) {
            link->attach(new chNode(node));
        }
    } else {
        linkNode *sibling = new linkNode();
        if (std::is_same<T, ASTNode>::value) {
            sibling->attach(node);
        } else if (std::is_same<T, std::string>::value) {
            sibling->attach(new stringNode(node))
        } else if (std::is_same<T, char>::value) {
            sibling->attach(new chNode(node));
        }
        link->append(sibling);
    }
    populate(type, nodes);
}

void ASTNode::populate(std::string type, ASTNode *node) {
    if (id != type) {
        id = type;
        link = new linkNode();
        link->attach(node);
    } else {
        linkNode *sibling = new linkNode();
        sibling->attach(node);
        link->append(sibling);
    }
}

void ASTNode::populate(std::string type, std::string node) {
    populate(type, new stringNode(node));
}

void ASTNode::populate(std::string type, char node) {
    populate(type, new chNode(node));
}