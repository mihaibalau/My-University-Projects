#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& sortedset;
	SortedSetIterator(const SortedSet& m);

	int* stack;
    int index_stack;
    int capacity_stack;
    int current_element;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

