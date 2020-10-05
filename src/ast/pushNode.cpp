#include "ASTNode.h"
#include <functional>

class pushNode: public ASTNode {
    public:
        pushNode(std::function<void*()> func);
        pushNode(rule *text);
        void* push();

    protected:
        std::function<void*()> func;
        rule *match;
        std::string which;
};
    
pushNode::pushNode(std::function<void*()> func) {
    id = "push";
    which = "func";
    func = func;
}

pushNode::pushNode(rule *text) {
    id = "push";
    which = "match";
    match = text;
}

void *pushNode::push() {
    if (which == "func") {
        return func();
    }
    return match;
}