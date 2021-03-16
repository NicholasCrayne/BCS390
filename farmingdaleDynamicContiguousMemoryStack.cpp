// (c) 2013-2020 David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// dynamic arrays, exceptions and operator overloading, and templates


// Class farmingdale::stack: General integer stack implementation based on array. 
// We will add dynamic arrays (for unlimited size), templates (to allow multiple types) etc.

// very minimal set of tests. 
#include <iostream>
#include <string>
#include <algorithm> // std::swap
#include "farmingdaleDynamicContiguousMemoryStack.h"


// Just a demonstration of how we *might* utilize the "using" directive
//using  farmingdale::FAILURE;
//using  farmingdale::SUCCESS;
//using  farmingdale::stack;

// This first block of code will not be compiled if TEMPLATED_STACK is defined. 
// Use this first block for your initial coding
// As we discuss in the videos, template code will end up in the header

#ifndef TEMPLATED_STACK
// Non Templated Code here

// test methods return 0 on success. Otherwise return the line number 
// on which the error occurred (For ease in finding it. Note that the 
// preprocessor directive __LINE__ will give you this line.
int studentTest() {
	return 0;
}

farmingdale::stack::stack()
	:
	countOfItems(0),
	capacity(INITIAL_STACK_SIZE)
{
	data = new std::string[capacity];
}

farmingdale::stack::stack(const stack& copyMe)
{
	this->capacity = copyMe.capacity;
	this->countOfItems = copyMe.countOfItems;
	std::string* newMemory = new std::string[capacity];
	std::string* temp;

	for (int i = 0; i < countOfItems; i++)
	{
		newMemory[i] = copyMe.data[i];
	}

	temp = this->data;
	this->data = newMemory;

	delete[] temp;
}

farmingdale::stack& farmingdale::stack::operator=(stack copyMe)
{
	std::swap(data, copyMe.data);
	capacity = copyMe.capacity;
	countOfItems = copyMe.countOfItems;
	return *this;
}

farmingdale::stack::~stack()
{
	delete[] data;
}

// Students will write the methods below:
farmingdale::statusCode farmingdale::stack::push(std::string insertMe)
{
	if (isFull())
	{
		int newCapacity = capacity * 2;
		std::string* theNewDataMemory;
		std::string* temp;
		try
		{
			theNewDataMemory = new std::string[newCapacity];
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

farmingdale::statusCode farmingdale::stack::peek(std::string& returnMe) const
{
	if (isEmpty())
	{
		return FAILURE;
	}

	returnMe = data[countOfItems - 1];

	return farmingdale::SUCCESS;
}



farmingdale::statusCode farmingdale::stack::pop(std::string& returnMe)
{
	if (isEmpty())
	{
		return FAILURE;
	}

	returnMe = data[countOfItems - 1];

	--countOfItems;

	return farmingdale::SUCCESS;
}

bool farmingdale::stack::operator==(const stack& rhs) const
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
void farmingdale::stack::printToStream(std::ostream& theStream) {
	theStream << "(bottom of stack)";
	for (int i = 0; i < countOfItems; ++i) {
		theStream << data[i] << (i < countOfItems - 1) ? ":" : "";
	}
	theStream << "(top of stack)" << std::endl;

}

#else //  TEMPLATED_STACK 
// Templated Code here

int studentTest() {
	return 0;
}


#endif // TEMPLATED_STACK