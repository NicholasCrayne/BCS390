// (c) 2013-2020 David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// dynamic arrays, exceptions and operator overloading, and templates


// Class farmingdale::stack: General integer stack implementation based on array. 
// We will add dynamic arrays (for unlimited size), templates (to allow multiple types) etc.

// very minimal set of tests. 
#include <iostream>
#include <string>
#include "farmingdaleContiguousMemoryStack.h"


// Just a demonstration of how we *might* utilize the "using" directive
//using  farmingdale::FAILURE;
//using  farmingdale::SUCCESS;
//using  farmingdale::stack;

// This first block of code will not be compiled if TEMPLATED_STACK is defined. 
// Use this first block for your initial coding
// As we discuss in the videos, template code will end up in the header

#ifndef TEMPLATED_STACK
int studentTest() {
	// In this method you may write your own simple tests
	// BE CAREFUL. YOU ARE NOT ALLOWED TO MODIFY The TEST FILE
	// at all 
	// test methods return 0 on success. Otherwise return the line number 
	// on which the error occurred (For ease in finding it. Note that the 
	// preprocessor directive __LINE__ will give you this line.
	return 0;
}



farmingdale::stack::stack()
{}

// Students will write the methods below:
farmingdale::statusCode farmingdale::stack::push(std::string insertMe) {
	return farmingdale::FAILURE;
}

farmingdale::statusCode farmingdale::stack::peek(std::string& returnMe) const {
	return farmingdale::FAILURE;
}



farmingdale::statusCode farmingdale::stack::pop(std::string& returnMe) {
	return farmingdale::FAILURE;
}




// Prewritten methods
void farmingdale::stack::printToStream(std::ostream& theStream) {
	theStream << "(bottom of stack)";
	for (int i = 0; i < countOfItems; ++i) {
		theStream << data[i] << (i < countOfItems - 1) ? ":" : "";
	}
	theStream << "(top of stack)" << std::endl;

}



#else //  TEMPLATED_STACK 

// test methods return 0 on success. Otherwise return the line number 
// on which the error occurred (For ease in finding it. Note that the 
// preprocessor directive __LINE__ will give you this line.
int studentTest() {
	return 0;
}

#endif // TEMPLATED_STACK