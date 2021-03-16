// (c) 2013-2020, David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// dynamic arrays, exceptions and operator overloading, and templates


// Class farmingdale::queue: General std::string queue implementation based on circular array. 
// We will add dynamic arrays (for unlimited size), templates (to allow multiple types) etc.

// very minimal set of tests. 
#include <iostream>
#include <string>
#include "farmingdaleContiguousMemoryQueue.h"


#ifndef TEMPLATED_QUEUE

// non-templated code


// test methods return 0 on success. Otherwise return the line number 
// on which the error occurred (For ease in finding it. Note that the 
// preprocessor directive __LINE__ will give you this line.
int studentTest() {
	return 0;
}

void farmingdale::queue::printToStream(std::ostream& theStream)
{
	theStream << "(Oldest)";
	for (int i = oldestIndex; i != nextInsertIndex; i = nextIndexOf(i))
	{
		theStream << data[i];
		if (nextIndexOf(i) != nextInsertIndex)
		{
			theStream << " ; ";
		}
	}
}

farmingdale::queue::queue()
{
	oldestIndex = 0;
	nextInsertIndex = 0;
}

farmingdale::queue::queue(const queue& copyMe)
{
	oldestIndex = copyMe.oldestIndex;
	nextInsertIndex = copyMe.nextInsertIndex;

	for (int i = oldestIndex; i != nextInsertIndex; i = nextIndexOf(i))
	{
		data[i] = copyMe.data[i];
	}
}

farmingdale::statusCode farmingdale::queue::peek(std::string &returnedElement) const
{
	if (isEmpty())
	{
		return farmingdale::FAILURE;
	}
	returnedElement = data[oldestIndex];
	return farmingdale::SUCCESS;
}

farmingdale::statusCode farmingdale::queue::dequeue(std::string &returnedElement)
{
	if (isEmpty())
	{
		return farmingdale::FAILURE;
	}
	returnedElement = data[oldestIndex];
	oldestIndex = nextIndexOf(oldestIndex);
	return farmingdale::SUCCESS;
}

farmingdale::statusCode farmingdale::queue::enqueue(std::string addMe)
{
	if (isFull())
	{
		return farmingdale::FAILURE;
	}
	data[nextInsertIndex] = addMe;
	nextInsertIndex = nextIndexOf(nextInsertIndex);
	return farmingdale::SUCCESS;
}

bool farmingdale::queue::operator==(const queue& rhs) const
{
	int myIterator = oldestIndex;
	int otherIterator = rhs.oldestIndex;

	while (myIterator != nextInsertIndex && otherIterator != rhs.nextInsertIndex)
	{
		if (data[myIterator] != rhs.data[otherIterator])
		{
			return false;
		}
		myIterator = nextIndexOf(myIterator);
		otherIterator = rhs.nextIndexOf(otherIterator);
	}

	if (myIterator != nextInsertIndex || otherIterator != rhs.nextInsertIndex)
	{
		return false;
	}

	return true;
}

#else // !TEMPLATED_QUEUE

// Templated code

// test methods return 0 on success. Otherwise return the line number 
// on which the error occurred (For ease in finding it. Note that the 
// preprocessor directive __LINE__ will give you this line.
int studentTest() {
	return 0;
}

#endif //  TEMPLATED_QUEUE