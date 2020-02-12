/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
// you may include more libraries as needed

using namespace std;

void displayMenu();
void handleUserInput(CountryNetwork& CountryNet);

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork CountryNet;

    // this will loop until user selects quit option
    handleUserInput(CountryNet);

    // quit: clean up.
    CountryNet.printPath();
    CountryNet.deleteEntireNetwork();
    if (CountryNet.isEmpty())
    {
        cout << "Path cleaned" << endl;
    }
    else
    {
        cout << "Error: Path NOT cleaned" << endl;
        CountryNet.printPath();
    }

    cout << "Goodbye!" << endl;
    return 0;
}

/*
 * Purpose: handle the interaction with the user
 * @param CountryNet object for carrying out country network operations
 * @return none
 */
void handleUserInput(CountryNetwork& CountryNet)
{
    bool quit = false;
    string s_input;
    int input;

    // loop until the user quits
    while (!quit)
    {
        displayMenu();

        // read in input, assuming a number comes in
        getline(cin, s_input);
        try
        {
            input = stoi(s_input);
        }
        catch (exception& e)
        {
            // non-numeric input. trigger the default switch case.
            input = 10;
        }

        switch (input)
        {
            // print all nodes
            case 1:     //rebuild network                
                CountryNet.loadDefaultSetup();
                CountryNet.printPath();
                break;

            case 2:        // print path
                CountryNet.printPath();
                break;

            case 3:
              {
                string newCountryName;
                string prevCountryName;
                cout << "Enter a new country name: " << endl;
                getline(cin, newCountryName);

                cout << "Enter the previous country name (or First): " << endl;
                getline(cin, prevCountryName);

                while(!CountryNet.searchNetwork(prevCountryName) and prevCountryName != "First")
                {
                  cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
                  getline(cin, prevCountryName);
                }

                // find the node containing prevcountry
                Country *tmp = NULL;
                if(prevCountryName !="First")
                {
                    tmp = CountryNet.searchNetwork(prevCountryName);
                }

                CountryNet.insertCountry(tmp, newCountryName);
                CountryNet.printPath();
              }
                break;

            case 4:     // delete country
              {
                string country;
                cout << "Enter a country name: " << endl;
                getline(cin, country);
                CountryNet.deleteCountry(country);
                CountryNet.printPath();
              }
                break;

              case 5:
              {
                cout<< " Enter the country name to loop back:"<<endl;
                string country;
                getline(cin, country);
                Country* lastnode = CountryNet.createLoop(country);
                bool hasLoop = CountryNet.detectLoop();
                if (hasLoop) {
                    cout << "Network contains a loop" << endl;
                    cout<< "Breaking the loop"<<endl;
                    lastnode->next = NULL;
                  } else {
                    cout << "Network does not contain a loop" << endl;
                  }

              }
            break;

            case 6:     // delete network
                //head = deleteEntireNetwork(head);
                {
                    string st, en;
                    cout << "Enter the start index: " << endl;
                    getline(cin, st);
                    cout << "Enter the end index: " << endl;
                    getline(cin, en);
                    CountryNet.readjustNetwork(stoi(st), stoi(en));
                    CountryNet.printPath();
                }
                break;
            case 7:
               {
                    cout <<"Network before deletion"<<endl;
                    CountryNet.printPath();
                    CountryNet.deleteEntireNetwork();
                    cout <<"Network after deletion"<<endl;
                    CountryNet.printPath();
               }
               break;
            case 8:     // quit
                quit = true;
                cout << "Quitting... cleaning up path: " << endl;
                break;

            default:     // invalid input
                cout << "Invalid Input" << endl;
                break;
        }
    }
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
    cout << " 3. Add Country " << endl;
    cout << " 4. Delete Country " << endl;
    cout << " 5. Create and Detect loop in Network" << endl;
    cout << " 6. Re-adjust Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
