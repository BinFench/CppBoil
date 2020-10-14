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
        std::cout << "Failed 1" << std::endl;
    }
    std::cout << passed << "/" << 2 << " cases pass" << std::endl;
    return 0;
}