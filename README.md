# CBoil
A parboiled inspired general PEG parser written in C++

## Motivations
CBoil is a derivative C++ implementation of [sirthias' Parboiled](https://github.com/sirthias/parboiled).  It is written entirely from scratch, but follows the interface Parboiled provides.  
Parboiled provides a very elegant method of generating parsers in Java and Scala, so CBoil intends to be a similar method for C++.  
CBoil is mostly loyal to the Parboiled implementation, so code written in Java shouldn't be too hard to transfer to a C++ project.  
However, due to the large differences between C++ and the languages Parboiled works on, CBoil has some specific changes and optimizations to cater to C++ development.

## Installation
CBoil is only dependent on the C++ standard library, and features present in C++17.  The makefile uses g++ as the compiler but any compiler supporting C++17 should work.  
After cloning this project, go to the src directory and use either make static or make lib to generate a static CBoil.o or a dynamic shared library, respectively.  
For a static build, CBoil can be included in your project using #include "CBoil/src/Cboil", assuming the project is in the same directory as the file you are including in.  
For a library build, CBoil can be included in your project using #include "CBoil"  
When compiling your project while using the shared library, use -lCBoil as a compile flag.  
## Usage
For example usage, see the Parboiled docs for a high level understanding and check the test file in source code for several examples.  
The main usage of CBoil is to implement a derived class based on the parser base class.  Reading [parser.h](https://github.com/BinFench/CBoil/blob/master/src/parser/parser.h) and [parser.cpp](https://github.com/BinFench/CBoil/blob/master/src/parser/parser.cpp) will show what features are available to the user.  
## Major differences
When rule building, any call to a parent rule that would cause a recursive loop isn't handled by CBoil the same way Parboiled handles it.  
To call a rule recursively, enclose the rule in the recursion() node.  
  
As well, CBoil extends the functionality of Parboiled with a regex rule.  Regular expressions can be used to match complicated string patterns in a single rule statement.
