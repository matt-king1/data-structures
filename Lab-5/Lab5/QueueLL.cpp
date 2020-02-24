#include <iostream>
#include "QueueLL.hpp"

using namespace std;

QueueLL::QueueLL()
{
    queueFront = nullptr;
    queueEnd = nullptr;
}

QueueLL::~QueueLL()
{
    while( !isEmpty() )
        dequeue();
}

bool QueueLL::isEmpty()
{
    /*if(queueFront == nullptr || queueEnd == nullptr)
        return true;
    return false;*/
    return (!queueFront || !queueEnd);
}

// TODO
void QueueLL::enqueue(int key)
{
    Node *nn = new Node;
    nn->key = key;
    nn->next = nullptr;

    if(isEmpty())
    {
        // queueFront = nn; linter error
        // queueEnd = nn;
    } else {
        // queueEnd->next = nn; linter error
        // queueEnd = nn;
    }
}

//TODO
void QueueLL::dequeue()
{
    if(!isEmpty())
    {
        if(queueFront->next == NULL)
        {
            delete queueFront;
            queueFront = nullptr;
            queueEnd = nullptr;
        } else {
            //Node* tmp = queueFront; Linter error
            queueFront = queueFront->next;
            //delete tmp;
        }
    } else {
        cout<<"queue is empty. can not deque"<<endl;
    }
}

int QueueLL::peek()
{
    if( !isEmpty() )
        return queueFront->key;
    else
    {
        cout<< " queue is empty. can not peek"<<endl;
        return -1;
    }
    //return 0;
}
