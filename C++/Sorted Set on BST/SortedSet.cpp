#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

SortedSet::SortedSet(Relation r) : relation(r){
    this->root_position = NULL_TELEM;
    this->elements_number = -1;
    this->first_empty = 0;
    this->capacity = 8;
    this->info = new TElem[this->capacity + 1];
    this->left = new int[this->capacity + 1];
    this->right = new int[this->capacity + 1];
    this->parent = new int[this->capacity + 1];

    for(int i = 0; i <= this->capacity; i++) {
        this->info[i] = NULL_TELEM;
        this->left[i] = NULL_TELEM;
        this->right[i] = NULL_TELEM;
        this->parent[i] = i+1;
    }
    this->parent[this->capacity] = NULL_TELEM;
}

void SortedSet::resize() {

    int new_capacity = this->capacity * 2;
    TElem* new_info = new TElem[new_capacity + 1];
    int* new_left = new int[new_capacity + 1];
    int* new_right = new int[new_capacity + 1];
    int* new_parent = new int[new_capacity + 1];

    for(int i = 0; i <= this->capacity; i++) {
        new_info[i] = this->info[i];
        new_left[i] = this->left[i];
        new_right[i] = this->right[i];
        new_parent[i] = this->parent[i];
    }

    for(int i = this->capacity + 1; i <= new_capacity; i++){
        new_info[i] = NULL_TELEM;
        new_left[i] = NULL_TELEM;
        new_right[i] = NULL_TELEM;
        new_parent[i] = i+1;
    }

    this->first_empty = this->capacity + 1;
    this->capacity = new_capacity;

    delete[] this->info;
    delete[] this->left;
    delete[] this->right;
    delete[] this->parent;
    this->info = new_info;
    this->left = new_left;
    this->right = new_right;
    this->parent = new_parent;

}

bool SortedSet::add(TComp elem) {
	if(this->elements_number == this->capacity)
        this->resize();

    int current_element = this->root_position;
    int parent_element = -1;
    while(current_element != NULL_TELEM){
        if(this->info[current_element] == elem)
            return false;
        parent_element = current_element;
        bool mama = relation(elem, this->info[current_element]);
        TElem tata = this->info[current_element];
        if(relation(elem, this->info[current_element]))
            current_element = this->left[current_element];
        else
            current_element = this->right[current_element];
    }

    int position = this->first_empty;
    if(this->root_position == NULL_TELEM)
        this->root_position = position;
    this->elements_number++;
    this->info[position] = elem;
    this->first_empty = this->parent[position];
    this->parent[position] = parent_element;

    if(parent_element != -1) {
        if (relation(elem, this->info[parent_element]))
            this->left[parent_element] = position;
        else
            this->right[parent_element] = position;
    }
/*
    for(int i = 0; i <= this->capacity ; i++)
        if(this->info[i] == NULL_TELEM)
            std::cout << "0 | ";
        else
            std::cout << this->info[i] << " | ";
    std::cout << "\n";
    for(int i = 0; i <= this->capacity ; i++)
        if(this->left[i] == NULL_TELEM)
            std::cout << "0 | ";
        else
            std::cout << this->left[i] << " | ";
    std::cout << "\n";
    for(int i = 0; i <= this->capacity ; i++)
        if(this->right[i] == NULL_TELEM)
            std::cout << "0 | ";
        else
            std::cout << this->right[i] << " | ";
    std::cout << "\n";
    for(int i = 0; i <= this->capacity ; i++)
        if(this->parent[i] == NULL_TELEM)
            std::cout << "0 | ";
        else
            std::cout << this->parent[i] << " | ";
    std::cout << "\n";
    for(int i = 0; i <=  this->capacity ; i++)
        std::cout << "----";
    std::cout << "\n";*/

	return true;
}

int SortedSet::find_minimum(int position) {
    while(this->left[position] != NULL_TELEM) {
        position = this->left[position];
    }
    return position;
}

bool SortedSet::remove(TComp elem) {
    bool found = false;
    int current_element = this->root_position;
    int parent_element = -1;

    while (current_element != NULL_TELEM) {
        if (this->info[current_element] == elem) {
            found = true;
            break;
        }
        parent_element = current_element;
        if (relation(elem, this->info[current_element]))
            current_element = this->left[current_element];
        else
            current_element = this->right[current_element];
    }

    if (!found)
        return false;

    if (this->left[current_element] == NULL_TELEM && this->right[current_element] == NULL_TELEM) {
        if (parent_element == -1) {
            this->root_position = NULL_TELEM;
        } else {
            if (this->left[parent_element] == current_element)
                this->left[parent_element] = NULL_TELEM;
            else
                this->right[parent_element] = NULL_TELEM;
        }
    } else if (this->left[current_element] != NULL_TELEM && this->right[current_element] != NULL_TELEM) {
        int pos_minimum = this->find_minimum(this->right[current_element]);
        this->info[current_element] = this->info[pos_minimum];
        this->remove(this->info[pos_minimum]);
    } else {
        int next_pos = (this->left[current_element] != NULL_TELEM) ? this->left[current_element] : this->right[current_element];
        if (parent_element == -1) {
            this->root_position = next_pos;
        } else {
            if (this->left[parent_element] == current_element)
                this->left[parent_element] = next_pos;
            else
                this->right[parent_element] = next_pos;
        }
        this->parent[next_pos] = parent_element;
    }

    this->info[current_element] = NULL_TELEM;
    this->left[current_element] = NULL_TELEM;
    this->right[current_element] = NULL_TELEM;
    this->parent[current_element] = this->first_empty;
    this->first_empty = current_element;
    this->elements_number--;

    return true;
}


bool SortedSet::search(TComp elem) const {

    int current_element = this->root_position;
    while(current_element != NULL_TELEM){
        if(this->info[current_element] == elem)
            return  true;
        if(relation(elem, this->info[current_element]))
            current_element = this->left[current_element];
        else
            current_element = this->right[current_element];
    }
	return false;
}

int SortedSet::size() const {
	return this->elements_number + 1;
}


bool SortedSet::isEmpty() const {
	if(this->elements_number == -1)
	    return true;
    return false;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	delete[] this->info;
    delete[] this->left;
    delete[] this->right;
    delete[] this->parent;
}


