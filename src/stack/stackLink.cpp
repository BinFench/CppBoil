#include "stackLink.h"
#include <iostream>

stackLink::stackLink() {
    isRule = false;
    hasItem = false;
    test = "neither";
}

stackLink::~stackLink() {
    std::cout << "stackLink" << std::endl;
    if (hasItem) {
        std::cout << "stackLink item" << std::endl;
        //delete item;
    }
}