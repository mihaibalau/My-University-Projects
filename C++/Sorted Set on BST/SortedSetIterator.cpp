#include "SortedSetIterator.h"
#include <exception>
#include <iostream>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : sortedset(m)
{
    this->capacity_stack = 10;
    this->stack = new int[this->capacity_stack];
    this->index_stack = -1;
    this->current_element = NULL_TELEM;
    this->first();
}

void SortedSetIterator::first() {
    delete[] this->stack;
    this->stack = new int[this->capacity_stack];
    this->index_stack = -1;

    int current_elem = sortedset.root_position;
    while (current_elem != NULL_TELEM) {

        if (this->index_stack + 1 == this->capacity_stack) {
            this->capacity_stack *= 2;
            int *new_stack = new int[this->capacity_stack];

            for (int i = 0; i < this->capacity_stack / 2; ++i) {
                new_stack[i] = this->stack[i];
            }

            delete[] this->stack;
            this->stack = new_stack;
        }

        this->stack[++this->index_stack] = current_elem;
        current_elem = sortedset.left[current_elem];
    }
    if (this->index_stack >= 0)
        this->current_element = this->stack[this->index_stack--];
    else
        this->current_element = NULL_TELEM;
}

void SortedSetIterator::next() {
    if (!valid())
        throw std::exception();

    if(sortedset.right[this->current_element] != NULL_TELEM){

        int current_elem = sortedset.right[this->current_element];
        while(current_elem != NULL_TELEM){

            if(this->index_stack + 1 == this->capacity_stack){
                this->capacity_stack *= 2;
                int* new_stack = new int[this->capacity_stack];

                for (int i = 0; i < this->capacity_stack / 2; ++i) {
                    new_stack[i] = this->stack[i];
                }

                delete[] this->stack;
                this->stack = new_stack;
            }

            this->stack[++this->index_stack] = current_elem;
            current_elem = sortedset.left[current_elem];
        }
        this->current_element = this->stack[this->index_stack--];
    }
    else {
        if(this->index_stack < 0)
            this->current_element = NULL_TELEM;
        else
            this->current_element = this->stack[this->index_stack--];
    }
}

TElem SortedSetIterator::getCurrent()
{
    if (!valid())
        throw std::exception();

    return sortedset.info[this->current_element];
}

bool SortedSetIterator::valid() const {
    return this->current_element != NULL_TELEM;
}
