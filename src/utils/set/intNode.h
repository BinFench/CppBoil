#include "node.h"

#ifndef INTNODE_H
#define INTNODE_H

class intNode: public node {
public:
    void attach(int child);
    int getChild();
    void increment();

protected:
    int child;
};

#endif