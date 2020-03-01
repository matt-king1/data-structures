/****************************************************************/
/*                  RPN Calculator Driver File                  */
/****************************************************************/
/*      TODO: Implement driver as described in the writeup      */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>
#include <string>
#include <iomanip>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' && !point) point = true;
      else if(s[i]=='.' && point) return false;
    }

    return true;
}

int main()
{
  // TODO - Declare a stack to hold the operands
  string input;

  RPNCalculator *rpn = new RPNCalculator();

  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;

  while(true)
  {
    cout << "#> ";
    getline(cin, input);

    /* TODO
       1. Read input (operators and operands) until you encounter a "="
       2. Use the isNumber function to check if the input is an operand
       3. push all operands to the stack
       4. If input is not an operand, call the compute function to evaluate
          the partial expression
    */
    if(input == "=")
    { 
      if(rpn->isEmpty())
      {
        cout << "No operands: Nothing to evaluate" << endl;
        return 1; // THIS COULD CAUSE AN ISSUE
      }

      float num = (float)rpn->peek()->number;
      rpn->pop();

      if(rpn->isEmpty())
      {
        cout << setprecision(4) << num << endl;
        return 1;
      } else {
        cout << "Invalid expression" << endl;
        return 1; // THIS COULD CAUSE AN ISSUE
      }
    }
    int num;

    if(isNumber(input))
    {
      try
      {
        num = stof(input);  // attempt to parse float from string
      } catch(std::invalid_argument &e) {
        cout << "Invalid input" << endl; 
        num = 6969; // default case
      }
      rpn->push(num); // push all operands onto stack
    } else {
      rpn->compute(input);
    }

  }

  /* TODO - If the stack is empty then print "No operands: Nothing to evaluate" */

  /* TODO - Validate the expression
      1. If valid then print the result
      2. Else, print "Invalid expression"*/

  return 0;
}
