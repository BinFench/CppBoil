#include "rule.h"
#include "../ast/ASTNode.h"

rule::rule(ASTNode *node) {
    node = node;
}

ASTNode *rule::getNode() {
    return node;
}