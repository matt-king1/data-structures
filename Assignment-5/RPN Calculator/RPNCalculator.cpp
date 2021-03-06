#include "RPNCalculator.hpp"

RPNCalculator::RPNCalculator()
{
    stackHead = NULL;
}

RPNCalculator::~RPNCalculator()
{
    while(stackHead)
    {
        pop();
    }
}

bool RPNCalculator::isEmpty() { return stackHead == NULL; }

void RPNCalculator::push(float number)
{
    Operand* newOp = new Operand{number, NULL};
    newOp->next = stackHead;
    stackHead = newOp;
}

void RPNCalculator::pop()
{
    if(!stackHead)
    {
        std::cout << "Stack empty, cannot pop an item." << std::endl;
        return;
    }
    Operand* tmp = stackHead;
    stackHead = stackHead->next;
    delete tmp;
}

Operand* RPNCalculator::peek()
{
    if(!stackHead)
    {
        std::cout << "Stack empty, cannot peek." << std::endl;
        return NULL;
    }
    return stackHead;
}

bool RPNCalculator::compute(std::string symbol)
{

    if(!stackHead)
    {
        std::cout << "err: not enough operands" << std::endl;
        return false;
    }

    float n1 = peek()->number;
    pop();

    if(!stackHead)
    {
        std::cout << "err: not enough operands" << std::endl;
        push(n1);
        return false;
    }

    float n2 = peek()->number;
    pop();

    if(!(symbol == "+" || symbol == "*"))
    {
        //std::cout << "err: invalid operation" << std::endl;
        //std::cout << "symbol: " << symbol;
        return false;
    }

    if(symbol == "+")
    {
        //std::cout << "adding " << n1 << " and " << n2 << std::endl;
        push((n1 + n2));
        return true;
    }

    if(symbol == "*")
    {
        //std::cout << "multiplying " << n1 << " and " << n2 << std::endl;
        push((n1 * n2));
        return true;
    }
}