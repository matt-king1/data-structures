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
  string input;

  RPNCalculator *rpn = new RPNCalculator();

  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;

  while(true)
  {
    cout << "#> ";
    getline(cin, input);

    if(input == "=")
    { 
      if(rpn->isEmpty())
      {
        cout << "No operands: Nothing to evaluate" << endl;
        return 0;
      }

      float num = (float)rpn->peek()->number;
      rpn->pop();

      if(rpn->isEmpty())
      {
        cout << setprecision(4) << num << endl;
        return 0;
      } else {
        cout << "Invalid expression" << endl;
        return 0;
      }
    }
    float num;

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
  return 0;
}
