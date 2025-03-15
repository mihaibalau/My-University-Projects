#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <iostream>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

bool prime_condition(TKey cheie){
    if(cheie % 2 == 0 && cheie != 2)
        return false;
    for(int i=3; i <= cheie/2; i+=2)
        if(cheie%i == 0)
            return false;
    return true;
}

void testNew(){
    cout << "Starting filter testing \n";
    SortedMultiMap smm = SortedMultiMap(relation1);
    for(int i=3; i <= 150; i+=2){
        smm.add(i%20, i);
    }
    smm.filter(prime_condition);
    SMMIterator it = smm.iterator();
    it.first();
    while(it.valid()){
        TElem  e = it.getCurrent();
        assert(prime_condition(e.first) == true);
        it.next();
    }
    smm.add(4, 3);
    it.first();
    while(it.valid()){
        TElem  e = it.getCurrent();
        assert(prime_condition(e.first) == true);
        it.next();
    }
    cout << "Filter tests ended \n";
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
}

