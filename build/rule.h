/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: declaration of rule.  Rule is the container
          for ASTNode children to parse a string.
*/

//  Forward declaration, see ASTNode.h.
class ASTNode;

#ifndef RULE_H
#define RULE_H

class rule {
    //  Container for ASTNodes.
    public:
        rule() {};
        rule(ASTNode *node);
        ASTNode* getNode();
        rule *copy();

    protected:
        ASTNode *node;
};

#endif