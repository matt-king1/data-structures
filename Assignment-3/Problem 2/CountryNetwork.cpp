/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <string>
#include <iostream>

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
    head = nullptr;
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
    if(previous == NULL)
    {
        cout << "adding: " << countryName << " (HEAD)" << endl;
        Country *tmp = new Country{countryName};
        tmp->next = head;
        head = tmp;
    } else
    {
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
        Country *tmp = new Country{countryName};
        tmp->next = previous->next;
        previous->next = tmp;
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup() {
    string names[] = {"United States", "Canada", "Brazil", "India", "China", "Australia"};
    
    Country *a = new Country{names[0]};
    cout<<"adding: "<<a->name<<" (HEAD)"<<endl;
    head = a;

    Country *b = new Country{names[1]};
    cout << "adding: " << b->name << " (prev: " << a->name << ")" << endl;
    head->next = b;

    Country *c = new Country{names[2]};
    cout << "adding: " << c->name << " (prev: " << b->name << ")" << endl;
    head->next->next = c;

    Country *d = new Country{names[3]};
    cout << "adding: " << d->name << " (prev: " << c->name << ")" << endl;
    head->next->next->next = d;

    Country *e = new Country{names[4]};
    cout << "adding: " << e->name << " (prev: " << d->name << ")" << endl;
    head->next->next->next->next = e;

    Country *f = new Country{names[5]};
    cout << "adding: " << f->name << " (prev: " << e->name << ")" << endl;
    head->next->next->next->next->next = f;
}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
Country* CountryNetwork::searchNetwork(string countryName) 
{
    Country *c = head;
    
    if (c == NULL) { return NULL; }
    
    do
    {
        if(c->name == countryName)
        {
            return c;
        }
        c = c->next;
    } while(c->next != NULL);
}

/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
    Country *c = head;
    
    
    do
    {
        if(c->name == receiver)
        {
            c->numberMessages++;
            c->message = message;
            cout << c->name << " [# messages received: " << c->numberMessages << "] received: " << c->message << endl;
            break;
        } else if (c->name != receiver)
        {
            c->numberMessages++;
            c->message = message;
            cout << c->name << " [# messages received: " << c->numberMessages << "] received: " << c->message << endl;

        }
        c = c->next;
    } while(c->next != NULL);
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
    cout << "== CURRENT PATH ==\n";
    if (head == nullptr)
    {
        cout << "nothing in path" << endl;
    }
    else
    {
        Country *c = head;

        do
        {
            if (c->next == nullptr)
            {
                cout << c->name << endl;
            } else
            {
                cout << c->name << " -> ";
                c = c->next;
            }
        } while (c->next != NULL);
        cout << "NULL\n";
    }
    cout << "===\n";
}
