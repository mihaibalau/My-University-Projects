#include <algorithm>
#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include "iostream"

SMMIterator::SMMIterator(const SortedMultiMap& map) : map(map), currentIndex(0) {

    this->sortedElements = new TElem[map.capacity + 1];
    this->size = 0;

    for (int i = 0; i < map.capacity; i++) {
        if (map.table[i].second != NULL_TVALUE && map.table[i].second != -111110) {
            this->sortedElements[this->size++] = map.table[i];
        }
    }

    for(int i = 0; i < this->size-1; i++)
        for(int j = i+1; j < this->size ; j++)
            if(!this->map.relation(this->sortedElements[i].first, this->sortedElements[j].first))
                swap(this->sortedElements[i], this->sortedElements[j]);

/*    std::sort(this->sortedElements, this->sortedElements + this->size,
              [this](const TElem& a, const TElem& b) {
                  return this->map.relation(a.first, b.first);
              });*/

    this->currentIndex = 0;
}

void SMMIterator::first(){
	this->currentIndex = 0;
}

void SMMIterator::next(){
	if(this->valid())
        this->currentIndex++;
    else
        throw exception();
}

bool SMMIterator::valid() const{
	return this->currentIndex < this->size;
}

TElem SMMIterator::getCurrent() const{
	if(this->valid())
        return sortedElements[currentIndex];
	throw exception();
}

SMMIterator::~SMMIterator() {
    delete[] this->sortedElements;
}


