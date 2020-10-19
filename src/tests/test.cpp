#include "../CBoil"
#include <iostream>

class calculator: public parser {
    public:
    rule *InputLine();
    rule *Expression();
    rule *Term();
    rule *Factor();
    rule *Parens();
    rule *Number();
    rule *Digits();
    rule *Digit();
};

calculator *calc = new calculator();

int *sum(arg *Arg) {
    int *num;
    *num = *(int*)Arg->get(0) + *(int*)Arg->get(1);
    return num;
}

int *sub(arg *Arg) {
    int *num;
    *num = *(int*)Arg->get(0) - *(int*)Arg->get(1);
    return num;
}

int *mult(arg *Arg) {
    int *num;
    *num = *(int*)Arg->get(0) * *(int*)Arg->get(1);
    return num;
}

int *divide(arg *Arg) {
    int *num;
    *num = *(int*)Arg->get(0) / *(int*)Arg->get(1);
    return num;
}

int *toi(arg *Arg) {
    std::cout << "This gets called" << std::endl;
    int *num;
    std::string *s = new std::string();
    s = static_cast<std::string*>(Arg->get(0));
    std::cout << "Fails here?" << std::endl;
    std::cout << *s << std::endl;
    std::cout << "hmm" << std::endl;
    *num = std::stoi(*s, nullptr, 10);
    std::cout << "uhh" << std::endl;
    std::cout << *num << std::endl;
    return num;
}

rule *expr() {
    return calc->Expression();
}

rule *calculator::InputLine() {
    return sequence(Expression(), EOI());
}

rule *calculator::Expression() {
    return sequence(
        Term(),
        zeroOrMore(
            firstOf(
                sequence('+', Term(), push(sum, pop(), pop())),
                sequence('-', Term(), swap(), push(sub, pop(), pop()))
            )
        )
    );
}

rule *calculator::Term() {
    return sequence(
        Factor(),
        zeroOrMore(
            firstOf(
                sequence('*', Factor(), push(mult, pop(), pop())),
                sequence('/', Factor(), swap(), push(divide, pop(), pop()))
            )
        )
    );
}

rule *calculator::Factor() {
    return firstOf(Number(), Parens());
}

rule *calculator::Parens() {
    return sequence('(', recursion(expr), ')');
}

rule *calculator::Number() {
    return sequence(
            Digits(),
            push(match()),
            push(toi, pop())
    );
}

rule *calculator::Digits() {
    return oneOrMore(Digit());
}

rule *calculator::Digit() {
    return charRange('0', '9');
}

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

    if (calc->parse("2", calc->InputLine())) {
        std::cout << "Accepted" << std::endl;
        int result = *(int*)calc->getResult();
        std::cout << result << std::endl;
        if (result == 2) {
            std::cout << "Passed" << std::endl;
            passed++;
        } else {
            std::cout << "Failed 37" << std::endl;
        }
    } else {
        std::cout << "Failed 37" << std::endl;
    }

    std::cout << passed << "/" << 37 << " cases pass" << std::endl;
    return 0;
}
