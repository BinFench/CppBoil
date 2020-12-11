/*
    Author: Ben Finch
    Email: benjamincfinch@gmail.com
    Desc: declaration of charSet.  charSet keeps a set of unique chars as well
          as count of each of their occurrences.
*/

#include "charNode.h"
#include "intNode.h"

#ifndef CHARSET_H
#define CHARSET_H

class charSet {
public:
    charSet();
    void add(char ch);
    int getLength();
    int getOccurrence(char ch);
    char getChar(int i);
    void addAny();
private:
    charNode *chars;
    intNode *occurrences;
    int length;
    int any;
};

#endif