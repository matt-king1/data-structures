#include <iostream>
#include <math.h>
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

// method to insert a new node within the table
bool HashTable::insertItem(int key) {

    int index = hashFunction(key);
    node* n = createNode(key, 0);

    // if there is no collision, do the following
    if(table[index] == 0) {
        table[index] = n;
        return true;
    }
    else {
        // if there is a collision, find the next index that is available
        numOfcollisionI++;
        int counter = 1;

        while(true) {

            // find the next index using quadratic
            int quadCalc = index + pow(counter, 2);
            quadCalc = quadCalc % tableSize;

            if(table[quadCalc] == 0) {
                table[quadCalc] = n;
                return true;
            }

            counter++;
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

    if(table[index] == 0) return 0;

    if(table[index]->key == key) return table[index]; // check where the first occurrence of key 

    numOfcollisionS++;

    int counter = 1;
    while(true) {  // locate the node

        // calculate the next index to be probed
        int quadCalc = index + pow(counter, 2);
        quadCalc = quadCalc % tableSize;

        // check index
        if(table[quadCalc] != 0)
            if(table[quadCalc]->key == key) return table[quadCalc];


        // increment the counter
        counter++;
    }
}
int HashTable::getInsert() {
    return numOfcollisionI;
}

int HashTable::getSearch() {
    return numOfcollisionS;
}