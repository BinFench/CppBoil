#include "CBoil"
#include <iostream>

int main()
{
    int passed = 0;
    parser *newParser = new parser();
    if (newParser->parse("pass", newParser->String("pass")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 1" << std::endl;
    }
    if (!newParser->parse("fail", newParser->String("pass")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 2" << std::endl;
    }
    if (newParser->parse("pass", newParser->any()))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 3" << std::endl;
    }
    if (!newParser->parse("", newParser->any()))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 4" << std::endl;
    }
    if (newParser->parse("pass", newParser->anyOf("pass")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 5" << std::endl;
    }
    if (!newParser->parse("fail", newParser->anyOf("pass", "succeed")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 6" << std::endl;
    }
    if (newParser->parse("pass", newParser->anyOf("fail", newParser->String("pass"))))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 7" << std::endl;
    }
    if (!newParser->parse("pas", newParser->anyOf(newParser->String("fail"), newParser->String("pass"))))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 8" << std::endl;
    }
    if (newParser->parse("p", newParser->ch('p')))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 9" << std::endl;
    }
    if (!newParser->parse("p", newParser->ch('f')))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 10" << std::endl;
    }
    if (newParser->parse("p", newParser->charRange('a', 'z')))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 11" << std::endl;
    }
    if (!newParser->parse("f", newParser->charRange(newParser->ch('g'), newParser->ch('z'))))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 12" << std::endl;
    }
    std::cout << passed << "/" << 12 << " cases pass" << std::endl;
    return 0;
}