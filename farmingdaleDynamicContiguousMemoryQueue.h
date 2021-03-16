// (c) 2013-2020 David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// dynamic arrays, exceptions and operator overloading, and templates


// Class farmingdale::queue: General std::string queue implementation based on circular array. 
// We will add dynamic arrays (for unlimited size), templates (to allow multiple types) etc.

// note: This is not thread safe--there are no mutexes or locks on the indexes.

// like #pragma once but more portable
#ifndef H_FARMINGDALECONTIGUOUSMEMORYQUEUE
#define H_FARMINGDALECONTIGUOUSMEMORYQUEUE


// Note to students. It's OK to #include in a library header (inside the guards). 
// but DO NOT add a "using" directive inside a library header
#include <string>
#include "farmingdaleStatus.h"

// See https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
// for some notes on what we're doing here.
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

// Two consts for student messages. These will give the line number and file of the 
const std::string TEMPLATED_HEADER_FILE = (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("\\/") + 1));
const int TEMPLATED_HEADER_LINE = (__LINE__ + 3); // must not add more comments or space...
// Please set these before you start on the relevant project: 
// Uncomment this to test a templated version of the stack code.
// #define TEMPLATED_QUEUE


#ifndef TEMPLATED_QUEUE
// This code section is for the initial [non-templated] version of the code.
namespace farmingdale {
	// Note: namespaces are additive, so you can add new elements to this namespace in other files or later
	class queue;
}
class farmingdale::queue {
private:
	static const int INITIAL_QUEUE_SIZE = 16; // This should remain the initial size of the dynamic array
	std::string* data; //  [INITIAL_QUEUE_SIZE] ;     // This should become a dynamic array in M5

	int oldestIndex;		// index of the oldest element in the queue
	int nextInsertIndex;	// index of the first empty spot
	int currentCapacity;
	
	// we use capacity. Note that since we want to distinguish between full and empty, we leave
	// a single empty space always in the circular array (see the slides and videos). Because of this, 
	// the array size used for the circular calculations is always one more than the available slots
	// given and index, returns the address of the next index in a circular array
	inline int nextIndexOf(int index) const { return((index + 1) % (currentQueueCapacity()+1)); } 
public:
	queue();
	// rule of threes
	queue(const queue& copyMe);
	~queue();
	queue& operator=(queue); // using the copy/swap idiom

	// returns the initial size without a reallocation of memory
	inline int initialQueueCapacity() const { return INITIAL_QUEUE_SIZE - 1; } 
	// returns the current queue capacity: same as initial except will change in dynamic
	inline int currentQueueCapacity() const { return currentCapacity - 1; } 

	inline bool isEmpty() const { return (oldestIndex == nextInsertIndex); }
	inline bool isFull() { return (nextIndexOf(nextInsertIndex) == oldestIndex); }
	statusCode enqueue(std::string addMe);
	statusCode dequeue(std::string &returnedElement);
	statusCode peek(std::string &returnedElement) const;
	// compare two queues
	bool operator==(const queue&) const;
	// print a stack to a stream (e.g., std::cout)
	void printToStream(std::ostream& outputStream);
};
inline std::ostream& operator<<(std::ostream& theStream, farmingdale::queue theQueue) {
	theQueue.printToStream(theStream);
	return theStream;
}
inline bool operator!=(const farmingdale::queue& lhs, const farmingdale::queue& rhs) {
	return (!(lhs == rhs));
}


#else 

namespace farmingdale {
	// Note: namespaces are additive, so you can add new elements to this namespace in other files or later
	template <class CL> class queue;
}
template <class CL> class farmingdale::queue {
private:
	static const int INITIAL_QUEUE_SIZE = 16; // This should remain the initial size of the dynamic array
	CL* data; //  [INITIAL_QUEUE_SIZE] ;     // This should become a dynamic array in M5

	int oldestIndex;		// index of the oldest element in the queue
	int nextInsertIndex;	// index of the first empty spot
	int currentCapacity;

	// we use capacity. Note that since we want to distinguish between full and empty, we leave
	// a single empty space always in the circular array (see the slides and videos). Because of this, 
	// the array size used for the circular calculations is always one more than the available slots
	// given and index, returns the address of the next index in a circular array
	inline int nextIndexOf(int index) const { return((index + 1) % (currentQueueCapacity() + 1)); }
public:
	queue();
	// rule of threes
	queue(const queue<CL>& copyMe);
	~queue();
	queue& operator=(queue<CL>); // using the copy/swap idiom

	// returns the initial size without a reallocation of memory
	inline int initialQueueCapacity() const { return INITIAL_QUEUE_SIZE - 1; }
	// returns the current queue capacity: same as initial except will change in dynamic
	inline int currentQueueCapacity() const { return currentCapacity - 1; }

	inline bool isEmpty() const { return (oldestIndex == nextInsertIndex); }
	inline bool isFull() { return (nextIndexOf(nextInsertIndex) == oldestIndex); }
	statusCode enqueue(CL addMe);
	statusCode dequeue(CL& returnedElement);
	statusCode peek(CL& returnedElement) const;
	// compare two queues
	bool operator==(const queue<CL>&) const;
	// print a stack to a stream (e.g., std::cout)
	void printToStream(std::ostream& outputStream);
};
template <class CL> inline std::ostream& operator<<(std::ostream& theStream, farmingdale::queue<CL> theQueue) {
	theQueue.printToStream(theStream);
	return theStream;
}
template <class CL> inline bool operator!=(const farmingdale::queue<CL>& lhs, const farmingdale::queue<CL>& rhs) {
	return (!(lhs == rhs));
}

template <class CL> void farmingdale::queue<CL>::printToStream(std::ostream& theStream)
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

template <class CL> farmingdale::queue<CL>::queue()
{
	oldestIndex = 0;
	nextInsertIndex = 0;
	currentCapacity = INITIAL_QUEUE_SIZE;

	data = new CL[currentCapacity];
}

template <class CL> farmingdale::queue<CL>::queue(const queue<CL>& copyMe)
{
	oldestIndex = copyMe.oldestIndex;
	nextInsertIndex = copyMe.nextInsertIndex;
	currentCapacity = copyMe.currentCapacity;

	data = new CL[currentCapacity];

	for (int i = oldestIndex; i != nextInsertIndex; i = nextIndexOf(i))
	{
		data[i] = copyMe.data[i];
	}
}

template <class CL> farmingdale::queue<CL>::~queue()
{
	delete[] data;
}

template <class CL> farmingdale::statusCode farmingdale::queue<CL>::peek(CL& returnedElement) const
{
	if (isEmpty())
	{
		return farmingdale::FAILURE;
	}
	returnedElement = data[oldestIndex];
	return farmingdale::SUCCESS;
}

template <class CL> farmingdale::statusCode farmingdale::queue<CL>::dequeue(CL& returnedElement)
{
	if (isEmpty())
	{
		return farmingdale::FAILURE;
	}
	returnedElement = data[oldestIndex];
	oldestIndex = nextIndexOf(oldestIndex);
	return farmingdale::SUCCESS;
}

template <class CL> farmingdale::statusCode farmingdale::queue<CL>::enqueue(CL addMe)
{
	if (isFull())
	{
		int newCapacity = currentCapacity * 2;
		CL* theNewDataMemory;
		CL* temp;
		int count = 0;

		try
		{
			theNewDataMemory = new CL[newCapacity];
		}
		catch (std::bad_alloc)
		{
			return farmingdale::FAILURE;
		}

		for (int i = oldestIndex; i != nextInsertIndex; i = nextIndexOf(i))
		{
			theNewDataMemory[count] = data[i];
			count++;
		}

		oldestIndex = 0;
		nextInsertIndex = count;

		temp = data;
		data = theNewDataMemory;

		currentCapacity = newCapacity;
		delete[] temp;
	}

	data[nextInsertIndex] = addMe;
	nextInsertIndex = nextIndexOf(nextInsertIndex);
	return farmingdale::SUCCESS;
}

template <class CL> bool farmingdale::queue<CL>::operator==(const queue<CL>& rhs) const
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

template <class CL> farmingdale::queue<CL>& farmingdale::queue<CL>::operator=(queue<CL> copyMe)
{
	std::swap(data, copyMe.data);
	oldestIndex = copyMe.oldestIndex;
	nextInsertIndex = copyMe.nextInsertIndex;
	currentCapacity = copyMe.currentCapacity;
	return *this;
}


#endif // TEMPLATED_QUEUE


#endif // H_FARMINGDALECONTIGUOUSMEMORYSTACK