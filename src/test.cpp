#include "CBoil"
#include <iostream>

int main()
{
    int passed = 0;
    parser *newParser = new parser();
    if (newParser->parse("pass", newParser->String("pass"))) {
        std::cout << "Passed" << std::endl;
        passed++;
    } else {
        std::cout << "Failed 1" << std::endl;
    }
    if (!newParser->parse("fail", newParser->String("pass"))) {
        std::cout << "Passed" << std::endl;
        passed++;
    } else {
        std::cout << "Failed 2" << std::endl;
    }
    if (newParser->parse("pass", newParser->any())) {
        std::cout << "Passed" << std::endl;
        passed++;
    } else {
        std::cout << "Failed 3" << std::endl;
    }
    if (!newParser->parse("", newParser->any())) {
        std::cout << "Passed" << std::endl;
        passed++;
    } else {
        std::cout << "Failed 4" << std::endl;
    }
    if (newParser->parse("pass", newParser->anyOf(newParser->String("pass")))) {
        std::cout << "Passed" << std::endl;
        passed++;
    } else {
        std::cout << "Failed 5" << std::endl;
    }
    if (!newParser->parse("fail", newParser->anyOf(newParser->String("pass"), newParser->String("succeed")))) {
        std::cout << "Passed" << std::endl;
        passed++;
    } else {
        std::cout << "Failed 6" << std::endl;
    }
    if (newParser->parse("pass", newParser->anyOf(newParser->String("fail"), newParser->String("pass")))) {
        std::cout << "Passed" << std::endl;
        passed++;
    } else {
        std::cout << "Failed 7" << std::endl;
    }
    if (!newParser->parse("pas", newParser->anyOf(newParser->String("fail"), newParser->String("pass")))) {
        std::cout << "Passed" << std::endl;
        passed++;
    } else {
        std::cout << "Failed 8" << std::endl;
    }
    std::cout << passed << "/" << 8 << " cases pass" << std::endl;
    return 0;
}