#include <CBoil>
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
    if (newParser->parse("p", newParser->empty()))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 13" << std::endl;
    }
    if (newParser->parse("", newParser->EOI()))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 14" << std::endl;
    }
    if (!newParser->parse("f", newParser->EOI()))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 15" << std::endl;
    }
    if (newParser->parse("pass", newParser->firstOf("fail", "pass", "succeed")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 16" << std::endl;
    }
    if (!newParser->parse("fail", newParser->firstOf(newParser->String("pass"), newParser->String("succeed"))))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 17" << std::endl;
    }
    if (newParser->parse("pass", newParser->ignoreCase("PaSs")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 18" << std::endl;
    }
    if (!newParser->parse("fAiL", newParser->ignoreCase("PaSs")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 19" << std::endl;
    }
    if (newParser->parse("pass", newParser->noneOf('f', 'l', 'y')))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 20" << std::endl;
    }
    if (!newParser->parse("fail", newParser->noneOf(newParser->ch('f'), 'l', 'y')))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 21" << std::endl;
    }
    if (!newParser->parse("pass", newParser->nothing()))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 22" << std::endl;
    }
    if (newParser->parse("passpass", newParser->oneOrMore("pass")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 23" << std::endl;
    }
    if (!newParser->parse("failpass", newParser->oneOrMore("pass")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 24" << std::endl;
    }
    if (newParser->parse("pass", newParser->optional(newParser->String("pass"))))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 25" << std::endl;
    }
    if (newParser->parse("pass", newParser->optional(newParser->String("fail"))))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 26" << std::endl;
    }
    if (newParser->parse("pass", newParser->regex(".*ass")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 27" << std::endl;
    }
    if (!newParser->parse("fail", newParser->regex(".*ass")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 28" << std::endl;
    }
    if (newParser->parse("pass", newParser->sequence('p', 'a', 's', 's')))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 29" << std::endl;
    }
    if (!newParser->parse("fail", newParser->sequence('f', 'a', 'i', 's')))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 30" << std::endl;
    }
    if (newParser->parse("pass", newParser->test(newParser->String("pass"))))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 31" << std::endl;
    }
    if (!newParser->parse("pass", newParser->test(newParser->String("fail"))))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 32" << std::endl;
    }
    if (newParser->parse("pass", newParser->testNot(newParser->String("fail"))))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 33" << std::endl;
    }
    if (!newParser->parse("fail", newParser->testNot(newParser->String("fail"))))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 34" << std::endl;
    }
    if (newParser->parse("passpass", newParser->zeroOrMore("pass")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 35" << std::endl;
    }
    if (newParser->parse("failpass", newParser->zeroOrMore("pass")))
    {
        std::cout << "Passed" << std::endl;
        passed++;
    }
    else
    {
        std::cout << "Failed 36" << std::endl;
    }
    std::cout << passed << "/" << 36 << " cases pass" << std::endl;
    return 0;
}