CC=g++
CFLAGS=-std=c++17
DEPS = arg.h parser/rule.h parser/parser.h ast/ASTNode.h ast/linkNode.h stack/stack.h stackLink.h
OBJ = parser/parser.o ast/ASTNode.o ast/linkNode.o parser/rule.o stack/stack.o stack/stackLink.o arg.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test.cpp: $(OBJ)
	$(CC) -g $@ $^ $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf stack/*.o
	rm -rf parser/*.o
	rm -rf ast/*.o