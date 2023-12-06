//Nicholas Singh
//DSA 2

#include <iostream>
#include "hash.h"
using namespace std;

//Initializing hashTable's capacity and size
hashTable::hashTable(int size) : capacity(getPrime(size)), data(capacity), filled(0){}

//Got the idea from https://www.w3docs.com/snippets/java/good-hash-function-for-strings.html
//Found the C++ implementation from https://github.com/sehee-lee/djb2
int hashTable::hash(const std::string &key){
	unsigned long hash = 5381;
    int c;
	int i = 0;
    while (c = key[i++])
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % capacity;
}

//Used to insert a new value to hash table
int hashTable::insert(const std::string &key, void *pv){
	int position = hash(key);

	//First search for the key in our hashTable and find first available spot
	while (data[position].isOccupied && (data[position].key != key)){
		position++;
		position %= capacity;
	}
	if (data[position].key == key){
		return 1;
	}

	//Rehash when more than half the capacity is full
	if(filled >= (capacity/2)){
		if(!rehash()){
			return 2;
		}
	}

	//Insert the new key
	data[position].key = key;
	data[position].pv = pv;
	data[position].isOccupied = true;
	data[position].isDeleted = false;
	filled++;
	return 0;
}

//Finds position given a key
int hashTable::findPos(const std::string &key){
	int position = hash(key);
	while (data[position].isOccupied){
		if (data[position].key == key){
			return position;
		}
		position++;
		position %= capacity;
	}
	return -1;
}

//Check if hash table contains key
bool hashTable::contains(const std::string &key){
	if(findPos(key) != -1){
		return true;
	}
	else{
		return false;
	}
}

//Rehash to copy data into a temp hash table, expand and reset the data table, and add the old values back into the new table
bool hashTable::rehash(){
    vector<hashItem> temp = data;
    try{
		data.resize(getPrime(capacity));
	}
    catch (std::bad_alloc){
        cout << "Error: Unable to Rehash" << endl;
        return false;
	}
    capacity = getPrime(capacity);
    filled = 0;
    for (int i = 0; i < data.size(); i++){
        data[i].key = "";
	    data[i].pv = nullptr;
        data[i].isOccupied = false;
        data[i].isDeleted = false;
		}
    for (int i = 0; i < temp.size(); i++){
        hashItem item = temp[i];
        if ((item.isOccupied == true) && (item.isDeleted == false)){
            insert(item.key, item.pv);
				}
    }
    return true;
}

unsigned int hashTable::getPrime(int size){ 
    const int primes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
    for(int prime : primes){
        if(prime > size)
            return prime; 
    }
    return -1;
}