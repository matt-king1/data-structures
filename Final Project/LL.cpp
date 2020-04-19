#include "LL.hpp"

using namespace std;
Node* LinkedList::search(unsigned int id)
{
    if(!head) return NULL;

    Node* curr = head;
    while(curr != NULL)
    {
        if(curr->key == id)
        {
            return curr;
        }
        curr = curr->next;
    }
}

void LinkedList::display()
{
    if(!head) return;

    Node* curr = head;
    while(curr != NULL)
    {
        cout << curr->key << " ";
        curr = curr->next;
    }
    cout << endl;
}

void LinkedList::insert(unsigned int id)
{
    if(!head) // we need to make a new head
    {
        Node* n = new Node(id);
        head = n;
        return;
    } else {
        // we need to find the last node
        Node* n = head;
        while(n->next != NULL)
        {
            n = n->next;
        }

        n->next = new Node(id);
    }
}

LinkedList::~LinkedList()
{   // use destructor to ensure we dont have memory leaks
    if(!head) return;

    Node* curr = head;
    while(curr != NULL)
    {
        Node* tmp = curr;
        curr = curr->next;
        delete tmp;
    }
}