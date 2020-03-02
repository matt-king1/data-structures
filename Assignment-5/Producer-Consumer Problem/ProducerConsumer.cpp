#include "ProducerConsumer.hpp"
#include <iostream>
#include <string>
#include <math.h>


using namespace std;

ProducerConsumer::ProducerConsumer()
{
    queueFront = -1;
    queueEnd = 0;
}

bool ProducerConsumer::isEmpty() { return queueFront == -1; }

bool ProducerConsumer::isFull() 
{
    return queueEnd == queueFront;
}

void ProducerConsumer::enqueue(std::string item)
{
    if(isFull())
    {
        cout << "Queue full, cannot add new item" << endl;
        return;
    }
    cout << "Adding " << item << " to queue" << endl;
    queue[queueEnd] = item;
    queueEnd = (queueEnd + 1) % SIZE;
}

void ProducerConsumer::dequeue()
{
    if(isEmpty())
    {
        cout << "Queue empty, cannot dequeue an item" << endl;
        return;
    }
    queueFront = (queueFront + 1) % SIZE;
}

std::string ProducerConsumer::peek()
{
    if(isEmpty())
    {
        cout << "Queue empty, cannot peek" << endl;
        return "";
    }
    return queue[queueFront];
}

int ProducerConsumer::queueSize()
{
    // via some guy on stackoverflow:
    int size = queueFront > queueEnd ? (queueFront - queueEnd) : (queueFront + SIZE - queueEnd);
}