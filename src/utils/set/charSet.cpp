#include "charSet.h"

charSet::charSet() {
    any = 0;
    length = 0;
}

void charSet::add(char ch) {
    if (length > 0) {
        bool first = true;
        node *currentChar = chars;
        node *currentInt = occurrences;

        do {
            if (!first) {
                currentChar = currentChar->getSibling();
                currentInt = currentInt->getSibling();
            } else {
                first = false;
            }
            if (currentChar->hasChild && ch == ((charNode *)currentChar)->getChild()) {
                ((intNode *)currentInt)->increment();
                return;
            }
        } while(currentChar->hasSibling);

        currentChar->hasSibling = true;
        charNode *newChar = new charNode();
        newChar->attach(ch);
        currentChar->append(newChar);
        currentInt->hasSibling = true;
        intNode *newInt = new intNode();
        newInt->attach(1);
        currentInt->append(newInt);
        length++;
    } else {
        chars = new charNode();
        occurrences = new intNode();
        chars->attach(ch);
        occurrences->attach(1);
        length++;
    }
}

int charSet::getLength() {
    return length;
}

int charSet::getOccurrence(char ch) {
    if (length > 0) {
        bool first = true;
        node *currentChar = chars;
        node *currentInt = occurrences;

        do {
            if (!first) {
                currentChar = currentChar->getSibling();
                currentInt = currentInt->getSibling();
            } else {
                first = false;
            }
            if (currentChar->hasChild && ch == ((charNode *)currentChar)->getChild()) {
                return ((intNode *)currentInt)->getChild();
            }
        } while (currentChar->hasSibling);
    }
    return 0;
}

char charSet::getChar(int i) {
    if (i < length) {
        node *currentChar = chars;
        for (int j = 0; j < i; j++) {
            currentChar = currentChar->getSibling();
        }
        if (currentChar->hasChild) {
            return ((charNode *)currentChar)->getChild();
        }
    }
    return '\0';
}

void charSet::addAny() {
    any++;
}