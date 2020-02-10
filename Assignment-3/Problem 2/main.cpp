/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <iostream>
#include <fstream>

void displayMenu();  // declaration for main's helper-function

using namespace std;
int main(int argc, char* argv[])
{
    CountryNetwork countryNet;
    displayMenu();
    string str;
    
    while(getline(cin,str))
    {
        int choice = stoi(str);
        string ct, ct2, msg, prev;
        switch(choice)
        {
            case 1:
                countryNet.loadDefaultSetup();
                countryNet.printPath();
                displayMenu();
                break;
            case 2:
                countryNet.printPath();
                displayMenu();
                break;
            case 3:
                cout << "Enter name of the country to receive the message:" << endl;
                getline(cin, ct);
                cout << "Enter the message to send:\n" << endl;
                getline(cin, msg);
                countryNet.transmitMsg(ct, msg);
                displayMenu();
                break;
            case 4:
                cout << "Enter a new country name:" << endl;
                getline(cin, ct2);
                cout << "Enter the previous country name (or First):" << endl;
                getline(cin, prev);
                if(prev == "First")
                {
                    countryNet.insertCountry(NULL, ct2);
                } else {
                    Country *p = countryNet.searchNetwork(prev);
                    countryNet.insertCountry(p, ct2);
                }
                displayMenu();
                break;
            case 5:
                cout << "Quitting...\nGoodbye!";
                break;
        }
    }

    return 0;
}


/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
