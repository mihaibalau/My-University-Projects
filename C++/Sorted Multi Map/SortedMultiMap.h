#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
#define DELETED_TELEM pair<TKey, TValue>(-111110, -111110);
using namespace std;
class SMMIterator;
typedef bool(*Condition)(TKey);
typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
	friend class SMMIterator;
    private:
		TElem* table;
        int table_size;
        int capacity; // m = capacity
        double loadFactorThreshold;

        Relation relation;
        int hashFunction(TKey k, int i) const;
        void resize_and_rehash();
    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multimap
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multimap is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will return the pairs as required by the relation (given to the constructor)
    SMMIterator iterator() const;

    void filter(Condition cond);

    // destructor
    ~SortedMultiMap();
};
