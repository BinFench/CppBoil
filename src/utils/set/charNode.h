#include "node.h"

#ifndef CHARNODE_H
#define CHARNODE_H

class charNode: public node {
public:
    void attach(char child);
    char getChild();

protected:
    char child;
};

#endif