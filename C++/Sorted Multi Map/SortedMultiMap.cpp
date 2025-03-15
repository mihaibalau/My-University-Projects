#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

//Complexity Theta(N), where N is the capacity
SortedMultiMap::SortedMultiMap(Relation r) : relation(r) {
	this->table_size = 0;
    this->capacity = 8;
    this->loadFactorThreshold = 0.7;
    this->table = new TElem[this->capacity];
    for(int i=0; i < capacity; i++)
        this->table[i] = std::make_pair(NULL_TVALUE, NULL_TVALUE);
}

//Complexity:
// BC = Theta(1), when the hash function point from iteration 0 to an empty position
// WC = Theta(N), where N is the array's capacity
// TC = O(N), where N is the array's capacity
void SortedMultiMap::add(TKey c, TValue v) {
    double ratio = static_cast<double>(this->table_size) / this->capacity;
    if(ratio > this->loadFactorThreshold)
        this->resize_and_rehash();

    int i = 0;
    int pos = hashFunction(c, i);
    while(this->table[pos].second != NULL_TVALUE){
        if(this->table[pos].second == -111110)
            break;
        i++, pos = hashFunction(c, i);
    }

    this->table[pos] = std::make_pair(c, v);
    this->table_size++;
}

//Complexity:
// BC = Theta(1), when the hash function point from iteration 0 to an empty position
// WC = Theta(N), where N is the array's capacity
// TC = O(N), where N is the array's capacity
vector<TValue> SortedMultiMap::search(TKey c) const {

    vector<TValue> values;
    int i = 0;
    int pos = hashFunction(c, i);

    while (this->table[pos].second != NULL_TVALUE && i < this->capacity) {
        if (this->table[pos].first == c) {
            values.push_back(this->table[pos].second);
        }
        pos = hashFunction(c, ++i);
    }

    return values;
}

//Complexity:
// BC = Theta(1), when the element is on first position in array
// WC = Theta(N), where N is the array's capacity
// TC = O(N), where N is the array's capacity
bool SortedMultiMap::remove(TKey c, TValue v) {

    int i = 0;
    int pos = hashFunction(c, i);

//    while (this->table[pos].second != NULL_TVALUE && i < this->capacity) {
//        if (this->table[pos].second == v) {
//            this->table[pos] = DELETED_TELEM;
//            this->table_size--;
//            return true;
//        }
//        pos = hashFunction(c, ++i);
//    }
//    return false;

    for(int i = 0; i < this->capacity; i++)
        if(this->table[i].second == v && this->table[i].first == c){
            this->table[i] = DELETED_TELEM;
            this->table_size--;
            return true;
        }
    return false;
}

//Complexity Theta(1)
int SortedMultiMap::size() const {
	return this->table_size;
}

//Complexity Theta(1)
bool SortedMultiMap::isEmpty() const {
	return !this->table_size;
}

//Complexity Theta(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

//Complexity Theta(1)
int SortedMultiMap::hashFunction(TKey k, int i) const {
    double c1 = 0.5, c2 = 0.5;
    return static_cast<int>(std::abs(k) % this->capacity + static_cast<double>(c1 * i) + static_cast<double>(c2 * i * i)) % this->capacity;
}

//Complexity:
// BC = Theta(N), where N is the array's capacity when hash function points from first iteration to an exmpty position
// WC = Theta(N^2), where N is the array's capacity
// TC = O(N^2), where N is the array's capacity
void SortedMultiMap::resize_and_rehash() {

    int old_capacity = this->capacity;
    this->capacity *= 2;
    TElem* new_table = new TElem[this->capacity];
    for(int i=0; i < this->capacity; i++)
        new_table[i] = std::make_pair(NULL_TVALUE, NULL_TVALUE);

    for(int j = 0; j < old_capacity; j++)
        if(this->table[j].second != NULL_TVALUE && this->table[j].second != -111110){

            int i = 0;
            int pos = hashFunction(this->table[j].first, i);
            while(new_table[pos].second != NULL_TVALUE)
                ++i, pos = hashFunction(this->table[j].first, i);

            new_table[pos] = this->table[j];
        }
    delete[] this->table;
    this->table = new_table;
}

//Complexity Theta(1)
SortedMultiMap::~SortedMultiMap() {
    delete[] this->table;
}

//Complexity Theta(N), where N is the array's size
void SortedMultiMap::filter(Condition cond) {

    for(int i = 0; i < this->capacity; i++)
        if(!cond(this->table[i].first)){
            this->table[i] = DELETED_TELEM;
            this->table_size--;
        }
}
