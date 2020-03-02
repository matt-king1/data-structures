#include "ProducerConsumer.hpp"
#include <iostream>
#include <string>
#include <math.h>


using namespace std;

ProducerConsumer::ProducerConsumer()
{
    queueFront = 0;
    queueEnd = 0;
}

bool ProducerConsumer::isEmpty() { return counter == 0; }

bool ProducerConsumer::isFull() { return counter == SIZE; }

void ProducerConsumer::enqueue(std::string item)
{
    if(isFull())
    {
        cout << "Queue full, cannot add new item" << endl;
        return;
    }
    queue[queueEnd] = item;
    queueEnd = (queueEnd + 1) % SIZE;
    counter++;
}

void ProducerConsumer::dequeue()
{
    if(isEmpty())
    {
        cout << "Queue empty, cannot dequeue an item" << endl;
        return;
    }
    queueFront = (queueFront + 1) % SIZE;
    counter--;
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
    // if(isEmpty()) return 0;
    // if(isFull()) return SIZE;
    // int size = queueFront > queueEnd ? (SIZE - queueFront + queueEnd) : (queueEnd - queueFront);
    // return size;
    return counter;
}