#include <iostream>
#include "hash3.hpp"

using namespace std;

// defualt constructor -- creates table of given size
HashTable::HashTable(int bsize) {

    tableSize = bsize;

    node* *arr = new node*[tableSize];
    table = arr;

    // set all pointers in the table equal to 0
    for(int i = 0; i < bsize; ++i) {
        table[i] = 0;
    }

}

// method to create a node within the table
node* HashTable::createNode(int key, node* next) {
    node* n = new node(); // create new node -- set the values for key and next
    n->key = key;
    n->next = next;

    return n; // returns the node pointer
}

// method that inserts a node
bool HashTable::insertItem(int key) {
    // create hash
    int index = hashFunction(key);
    node* n = createNode(key, 0); // create new node

    // if there is no collision, do the following
    if(table[index] == 0) {
        table[index] = n;
        return true;
    }
    else {
        // if there is a collision, find the next index that is available
        numOfcollisionI++;

        while(true) {
            index++;

            // check if the end is reach, if so -- start from the beginning
            if(index == tableSize) index = 0;

            if(table[index] == 0) {
                table[index] = n;
                return true;
            }
        }
    }
}


// method that returns a value from 0 to 39,999
unsigned int HashTable::hashFunction(int key) {
    return (key % tableSize);
}

// method that prints the entire table
void HashTable::printTable() {
    // print curr nodes
    for(int i = 0; i < tableSize; ++i) {
        // if node is not 0, do the following
        if(table[i] != 0)
            cout << "[" << i << "] -> " << table[i]->key << endl;
    }
}


// method that searches for a given value within the table
node* HashTable::searchItem(int key) {

    int index = hashFunction(key); // hash the key
    int temp = index;

    // checks if table is empty
    if(table[index] == 0) return 0;

    if(table[index]->key == key) return table[index];
    numOfcollisionS++;

    // while loop that finds the node
    while(true) {
        
        index++;
        if(table[index]->key == key) return table[index];
        
        if(index == tableSize - 1) index = 0; // if index reaches the last value, start over

        if(index == temp) return 0;
    }
}
int HashTable::getInsert() {
    return numOfcollisionI;
}

int HashTable::getSearch() {
    return numOfcollisionS;
}