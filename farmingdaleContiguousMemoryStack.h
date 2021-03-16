// (c) 2013-2020 David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// dynamic arrays, exceptions and operator overloading, and templates


// Class farmingdale::stack: General std::string stack implementation based on array. 
// We will add dynamic arrays (for unlimited size), templates (to allow multiple types) etc.

// note: This is not thread safe--there are no mutexes or locks on the indexes.

// like #pragma once but more portable
#ifndef H_FARMINGDALECONTIGUOUSMEMORYSTACK
#define H_FARMINGDALECONTIGUOUSMEMORYSTACK


// Note to students. It's OK to #include in a library header (inside the guards). 
// but DO NOT add a "using" directive inside a library header
#include <string>
#include "farmingdaleStatus.h"

// Two consts for student messages
const std::string TEMPLATED_HEADER_FILE = (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("\\/") + 1));
const int TEMPLATED_HEADER_LINE = (__LINE__ + 3);
// Please set these before you start on the relevant project: 
// Uncomment this to test a templated version of the stack code.
// #define TEMPLATED_STACK


#ifndef TEMPLATED_STACK
// This code section is for the initial [non-templated] version of the code.
namespace farmingdale {
	// Note: namespaces are additive, so you can add new elements to this namespace in other files or later
	class stack;
}


class farmingdale::stack {
private:
	static const int INITIAL_STACK_SIZE = 16;		  // in M3: This should remain the initial size of the dynamic array
	std::string data[INITIAL_STACK_SIZE];			  // in M3: This should become a dynamic array

	int countOfItems; // index of the first empty spot
public: 
	stack();

	// returns the initial size without a reallocation of memory
	inline int initialStackCapacity() const { return INITIAL_STACK_SIZE; } 
	// returns the current queue capacity: same as initial except will change in dynamic
	inline int currentStackCapacity() const { return INITIAL_STACK_SIZE; } 

	inline bool isEmpty() const { return (0 == countOfItems); }
	inline bool isFull() const { return (INITIAL_STACK_SIZE==countOfItems); }
	statusCode push(std::string addMe);
	statusCode pop(std::string &returnedElement);
	statusCode peek(std::string &returnedElement) const;
	// compare two stacks
	bool operator==(const stack&) const;
	// print a stack to a stream (e.g., std::cout)
	void printToStream(std::ostream& outputStream);
};
inline std::ostream& operator<<(std::ostream& theStream, farmingdale::stack theStack) {
	theStack.printToStream(theStream);
	return theStream;
}

#else 
// This is the TEMPLATED_STACK code, for the templated version of Stack


#endif // TEMPLATED_STACK


#endif // H_FARMINGDALECONTIGUOUSMEMORYSTACK