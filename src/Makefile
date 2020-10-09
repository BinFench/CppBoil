CC=g++
CFLAGS=-I.
DEPS = arg.h parser/rule.h parser/parser.h ast/ASTNode.h ast/linkNode.h stack/stack.h stackLink.h
OBJ = ast/anyNode.o ast/anyOfNode.o ast/ASTNode.o ast/charRangeNode.o ast/chNode.o ast/emptyNode.o ast/EOINode.o ast/firstOfNode.o ast/ignoreCaseNode.o ast/linkNode.o ast/matchNode.o ast/noneOfNode.o ast/nothingNode.o ast/oneOrMoreNode.o ast/optionalNode.o ast/peekNode.o ast/popNode.o ast/pushNode.o ast/recursionNode.o ast/regexNode.o ast/sequenceNode.o ast/stringNode.o ast/swapNode.o ast/testNode.o ast/testNotNode.o ast/zeroOrMoreNode.o parser/parser.o parser/rule.o stack/stack.o stack/stackLink.o arg.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf stack/*.o
	rm -rf parser/*.o
	rm -rf ast/*.o