CC=g++
CPPFLAGS= -std=c++17 -fPIC
DEPS = arg.h parser/rule.h parser/parser.h ast/ASTNode.h ast/linkNode.h stack/stack.h stackLink.h
OBJ = parser/parser.o ast/ASTNode.o ast/linkNode.o parser/rule.o stack/stack.o stack/stackLink.o arg.o

default:
	echo "Please either make static or make lib"

tests/test.cpp: CBoil.o
	$(CC) $@ $^ -o test -std=c++17
	./test
	rm -rf CBoil.o

memtest: CBoil.o
	$(CC) tests/test.cpp $^ -o test -std=c++17
	valgrind --tool=memcheck --leak-check=yes ./test

CBoil.o: $(OBJ)
	ld -r $^ -o CBoil.o
	rm -rf arg.o
	rm -rf stack/*.o
	rm -rf parser/*.o
	rm -rf ast/*.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

lib: CBoil.o
	$(CC) -shared -o libCBoil.so $^ $(CPPFLAGS)
	sudo cp libCBoil.so /usr/lib
	sudo mkdir /usr/include/CBoilBuild
	sudo cp ../build/* /usr/include/CBoilBuild/
	sudo cp ../CBoil /usr/include/CBoil
	sudo chmod 0755 /usr/lib/libCBoil.so
	rm CBoil.o
	rm libCBoil.so
	echo "Shared library created."

static: CBoil.o
	echo "Static object created."

libtest: lib
	$(CC) tests/libtest.cpp -o test -lCBoil -std=c++17 -fPIE
	./test

remove:
	sudo rm /usr/include/CBoil
	sudo rm -rf /usr/include/CBoilBuild
	sudo rm /usr/lib/libCBoil.so	

clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf *.out
	rm -rf stack/*.o
	rm -rf parser/*.o
	rm -rf ast/*.o
	rm test