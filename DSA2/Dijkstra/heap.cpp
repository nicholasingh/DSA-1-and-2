//Nicholas Singh
//DSA 2

#include <iostream>
#include <limits.h>
#include <climits>
#include "heap.h"
using namespace std;

heap::heap(int capacity){
    data.resize(capacity+1);
    mapping = new hashTable(capacity * 2);
    this->capacity = capacity;
    filled = 0;
}

int heap::insert(const std::string &id, int key, void *pv){
    if (filled == capacity){
        return 1;
    }
    
    if (!(mapping->contains(id))){
        filled ++;
        data[filled].id = id;
        data[filled].key = key;
        data[filled].pData = pv;
        mapping->insert(id, &data[filled]);
        percolateUp(filled);

        return 0;
    }
    else{
        return 2;
    }
}

int heap::setKey(const std::string &id, int key){

    node *pn = static_cast<node *>(mapping->getPointer(id)); 

    if(pn == nullptr){
        return 1;
    }

    int oldKey = pn->key;
    pn->key = key;
    int position = getPos(pn);

    if (key > oldKey){
        percolateDown(position);
    }
    else if (key < oldKey){
        percolateUp(position);
    }
    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    if (filled == 0){
        return 1;
    }
    else{
        node min = data[1];
        mapping->remove(min.id);
        if (pKey != nullptr){
            *pKey = min.key;
        }
        if (pId != nullptr){
            *pId = min.id;
        }
        if (ppData != nullptr){
            *(static_cast<void **> (ppData)) = data[1].pData;
        }

        data[1] = data[filled--];
        percolateDown(1);
        return 0;
    }
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
    if (!(mapping->contains(id))){ 
        return 1;
    }

    node *pn = static_cast<node *>(mapping->getPointer(id));

    if (ppData != nullptr){
        *(static_cast<void **> (ppData)) = pn->pData;
    }
    if (pKey != nullptr){
        *pKey = pn->key;
    }
    setKey(id, INT_MIN);
    deleteMin();
    return 0;
}

void heap::percolateUp(int posCur){
    data[0] = data[posCur];
    node tempAdd = data[posCur];
    for (; posCur > 1 && tempAdd.key < data[posCur / 2].key; posCur /= 2){
        data[posCur] = data[posCur / 2];
        mapping->setPointer(data[posCur].id, &data[posCur]);
    }
    data[posCur] = data[0];
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateDown(int posCur){
    int child;
    node tempGone = data[posCur];
    for (; posCur * 2 <= filled; posCur = child){
        child = posCur * 2;
        if (child != filled && data[child + 1].key < data[child].key){
            child++;
        }
        if (data[child].key < tempGone.key){ 
            data[posCur] = data[child];
            mapping->setPointer(data[posCur].id, &data[posCur]);
        }
        else{
            break;
        }
    }
    data[posCur] = tempGone;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node *pn){
    return (pn - &data[0]);
}