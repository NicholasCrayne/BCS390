// (c) 2013-2020 David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// dynamic arrays, exceptions and operator overloading, and templates


// Class farmingdale::stack: General std::string stack implementation based on array. 
// We will add dynamic arrays (for unlimited size), templates (to allow multiple types) etc.

// note: This is not thread safe--there are no mutexes or locks on the indexes.

// like #pragma once but more portable
#ifndef H_FARMINGDALEDYNAMICCONTIGUOUSMEMORYSTACK
#define H_FARMINGDALEDYNAMICCONTIGUOUSMEMORYSTACK

// Note to students. It's OK to #include in a library header (inside the guards). 
// but DO NOT add a "using" directive inside a library header
#include <string>
#include "farmingdaleStatus.h"

// See https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
// for some notes on what we're doing here.
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

// Two consts for   student messages
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
	std::string* data; //  [INITIAL_STACK_SIZE] ;			  // in M3: This should become a dynamic array
	int capacity; 
	int countOfItems; // index of the first empty spot
public: 
	stack();
	// Rule of threes
	stack(const stack&);
	~stack();
	// copy/swap idiom
	stack& operator=( stack);

	// returns the initial size without a reallocation of memory
	inline int initialStackCapacity() const { return INITIAL_STACK_SIZE; } 
	// returns the current queue capacity: same as initial except will change in dynamic
	inline int currentStackCapacity() const { return capacity; } 

	inline bool isEmpty() const { return (0 == countOfItems); }
	inline bool isFull() const { return (currentStackCapacity()==countOfItems); }
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
namespace farmingdale {
	// Note: namespaces are additive, so you can add new elements to this namespace in other files or later
	template <class CL> class stack;
}

template <class CL> class farmingdale::stack {
private:
	static const int INITIAL_STACK_SIZE = 16;		  // in M3: This should remain the initial size of the dynamic array
	CL data[INITIAL_STACK_SIZE];			  // in M3: This should become a dynamic array

	int capacity;
	int countOfItems; // index of the first empty spot
public:
	stack();
	// Rule of threes
	stack(const stack<CL>&);
	~stack();
	// copy/swap idiom
	stack& operator=(stack<CL>);

	// returns the initial size without a reallocation of memory
	inline int initialStackCapacity() const { return INITIAL_STACK_SIZE; }
	// returns the current queue capacity: same as initial except will change in dynamic
	inline int currentStackCapacity() const { return INITIAL_STACK_SIZE; }

	inline bool isEmpty() const { return (0 == countOfItems); }
	inline bool isFull() const { return (INITIAL_STACK_SIZE == countOfItems); }
	statusCode push(CL addMe);
	statusCode pop(CL& returnedElement);
	statusCode peek(CL& returnedElement) const;
	// compare two stacks
	bool operator==(const stack<CL>&) const;
	// print a stack to a stream (e.g., std::cout)
	void printToStream(std::ostream& outputStream);
};
template <class CL> inline std::ostream& operator<<(std::ostream& theStream, farmingdale::stack<CL> theStack) {
	theStack.printToStream(theStream);
	return theStream;
}


template <class CL> farmingdale::stack<CL>::stack()
	:
	countOfItems(0),
	capacity(INITIAL_STACK_SIZE)
{
	data = new CL[capacity];
}

template <class CL> farmingdale::stack<CL>::stack(const stack<CL>& copyMe)
{
	this->capacity = copyMe.capacity;
	this->countOfItems = copyMe.countOfItems;
	CL* newMemory = new CL[capacity];
	CL* temp;

	for (int i = 0; i < countOfItems; i++)
	{
		newMemory[i] = copyMe.data[i];
	}

	temp = this->data;
	this->data = newMemory;

	delete[] temp;
}

template <class CL> farmingdale::stack<CL>& farmingdale::stack<CL>::operator=(stack<CL> copyMe)
{
	std::swap(data, copyMe.data);
	capacity = copyMe.capacity;
	countOfItems = copyMe.countOfItems;
	return *this;
}

template <class CL> farmingdale::stack<CL>::~stack()
{
	delete[] data;
}

// Students will write the methods below:
template <class CL> farmingdale::statusCode farmingdale::stack<CL>::push(CL insertMe)
{
	if (isFull())
	{
		int newCapacity = capacity * 2;
		CL* theNewDataMemory;
		CL* temp;
		try
		{
			theNewDataMemory = new CL[newCapacity];
		}
		catch (std::bad_alloc)
		{
			return farmingdale::FAILURE;
		}

		for (int i = 0; i < countOfItems; i++)
		{
			theNewDataMemory[i] = data[i];
		}

		temp = data;
		data = theNewDataMemory;

		capacity = newCapacity;
		delete[] temp;
	}

	data[countOfItems] = insertMe;

	++countOfItems;

	return farmingdale::SUCCESS;
}

template <class CL> farmingdale::statusCode farmingdale::stack<CL>::peek(CL& returnMe) const
{
	if (isEmpty())
	{
		return FAILURE;
	}

	returnMe = data[countOfItems - 1];

	return farmingdale::SUCCESS;
}



template <class CL> farmingdale::statusCode farmingdale::stack<CL>::pop(CL& returnMe)
{
	if (isEmpty())
	{
		return FAILURE;
	}

	returnMe = data[countOfItems - 1];

	--countOfItems;

	return farmingdale::SUCCESS;
}

template <class CL> bool farmingdale::stack<CL>::operator==(const stack<CL>& rhs) const
{
	if (countOfItems != rhs.countOfItems)
	{
		return false;
	}

	for (int i = 0; i <= countOfItems; i++)
	{
		if (data[i] != rhs.data[i])
		{
			return false;
		}
	}

	return true;
}


// Prewritten methods
template <class CL> void farmingdale::stack<CL>::printToStream(std::ostream& theStream) {
	theStream << "(bottom of stack)";
	for (int i = 0; i < countOfItems; ++i) {
		theStream << data[i] << (i < countOfItems - 1) ? ":" : "";
	}
	theStream << "(top of stack)" << std::endl;

}


#endif // TEMPLATED_STACK


#endif // H_FARMINGDALEDYNAMICCONTIGUOUSMEMORYSTACK