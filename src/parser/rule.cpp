#include "rule.h"

rule::rule(ASTNode *nnode) {
    node = nnode;
}

ASTNode *rule::getNode() {
    return node;
}