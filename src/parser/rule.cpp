#include "rule.h"
#include "../ast/ASTNode.h"

rule::rule(ASTNode *nnode) {
    node = nnode;
}

ASTNode *rule::getNode() {
    return node;
}
rule::~rule() {
    delete node;
}