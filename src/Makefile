CC=g++
CFLAGS=-I.
DEPS = arg.h parser/rule.h parser/parser.h ast/ASTNode.h ast/linkNode.h stack/stack.h stackLink.h
OBJ = ast/ASTNode.o ast/linkNode.o parser/parser.o parser/rule.o stack/stack.o stack/stackLink.o arg.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf stack/*.o
	rm -rf parser/*.o
	rm -rf ast/*.o