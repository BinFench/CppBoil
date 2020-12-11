#ifndef NODE_H
#define NODE_H

class node {
public:
    node() {};
    void append(node *sibling);
    bool hasSibling;
    bool hasChild;
    node *getSibling();
    ~node();

protected:
    node *sibling;
};

#endif