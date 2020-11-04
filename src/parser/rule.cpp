/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: implementation of rule defined in rule.h.  Rule is the container
          for ASTNode children to parse a string.
*/
#include "rule.h"
#include "../ast/ASTNode.h"

rule::rule(ASTNode *nnode) {
    hasNode = true;
    node = nnode;
}

ASTNode *rule::getNode() {
    return node;
}

//  Copy function for memory management.
rule *rule::copy() {
    rule *newRule = new rule();
    newRule->node = node->copy();
    return newRule;
}