#include "rule.h"
#include "../ast/ASTNode.h"
#include <iostream>

rule::rule(ASTNode *nnode) {
    node = nnode;
}

ASTNode *rule::getNode() {
    return node;
}