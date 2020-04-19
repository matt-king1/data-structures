#ifndef LL_HPP
#define LL_HPP

#include <string>
#include <iostream>

struct Node
{
    unsigned int key;
    Node* next;

    Node(unsigned int k)
    {
        key = k;
        next = NULL;
    }
};

class LinkedList
{
    private:
        // pointer to head node
        Node* head;
    public:
        void insert(unsigned int id);
        void display();
        Node* search(unsigned int id);

        LinkedList()
        {
            head = NULL;
        }

        ~LinkedList();
};

#endif