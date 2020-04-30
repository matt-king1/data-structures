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

bool HashTable::insertItem(int key) {
    int index = hashFunction(key);
    node* newNode = createNode(key, 0);

    if(table[index] == 0)
    {
        table[index] = newNode;

        return true;
    }

    else 
    {
        numOfcollisionI++;

        node* temp = table[index];
        table[index] = newNode;
        newNode->next = temp;

        return true;
    }
}


// method that returns a value from 0 to 39,999
unsigned int HashTable::hashFunction(int key) {
    return (key % tableSize);
}

//method that prints the entire table
void HashTable::printTable() {

    for(int i = 0; i < tableSize; ++i) {
        if(table[i] != 0x0) // print following nodes if they are not equal to 0
        {
            cout << "[" << i << "] -> " << table[i]->key;
            node* temp = table[i]->next;

            while(temp != 0x0)
            {
                cout << " -> " << temp->key;
                temp = temp->next;
            }
            cout << endl;
        }
    }
}


// method that searches for a given value within the table
node* HashTable::searchItem(int key) {
    int index = hashFunction(key);

    if(table[index] == 0) return 0;
    
    else if(table[index]->key == key) {
        return table[index];
    }

    else{
        numOfcollisionS++;
        node* temp = table[index];

        while(temp != 0)
        {
            if(temp->key == key)
            {
                return temp;
            }

            temp = temp->next;
        }
    }

    return 0;
}
int HashTable::getInsert() {
    return numOfcollisionI;
}

int HashTable::getSearch() {
    return numOfcollisionS;
}