#include <string>
#include "linkNode.h"
#include "../stack/stack.h"

#ifndef ASTNODE_H
#define ASTNODE_H

class ASTNode {
    public:
        virtual bool parse(std::string *source, linkNode* path);
        virtual void *act(stack *values);
        std::string getId();

    protected:
        std::string id;
        linkNode* link;

        template<typename T, typename... Args>
        void populate(std::string type, T *node, Args... nodes);
        void populate(std::string type, ASTNode *node);
        void populate(std::string type, std::string node);
        void populate(std::string type, char node);
};

#endif