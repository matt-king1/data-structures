#include "hash.hpp"
#include <iostream>

using namespace std;
HashTable::HashTable(int bsize)
{
    tableSize = bsize;
}

unsigned int HashTable::hashFunction(int key)
{
    return key % tableSize;
}

bool HashTable::insertItem(int key)
{
    int index = hashFunction(key);
    cout << table[index] << endl;
}