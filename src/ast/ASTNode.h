#include <string>
#include <linkNode.h>

class ASTNode {
    friend class linkNode;

    protected:
        std::string id;
        linkNode* link;
}