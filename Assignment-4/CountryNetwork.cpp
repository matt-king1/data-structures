/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represent communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
/* finished. do not touch. */
    head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) {
    
    // if we are passed an empty list, just create a new head node, and return
    if (head == NULL)
    {
        cout << "adding: " << countryName << " (HEAD)" << endl;
        head = new Country;
        head->name = countryName;
        head->numberMessages = 0;
        head->next = NULL;
    }
    // if it's not empty, we need to search for previous and append our node there.
    else if(previous == NULL )
    {
        //case where it's a new head Country
        cout << "adding: " << countryName << " (HEAD)" << endl;
        Country *c = new Country;
        c->name = countryName;
        c->numberMessages = 0;
        c->next = head;
        head = c;
    }else{
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
        Country *newCountry = new Country;
        newCountry->name = countryName;
        newCountry->numberMessages = 0;
        newCountry->next = previous->next;
        previous->next = newCountry;
    }
}


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {
    Country* prev = head;

    if(prev->name == countryName){
        // found country at head
        // rewiring and deleting
        Country *tmp = head;
        head = head->next;
        delete tmp;
    } else {
        Country *curr = head->next; // to hold current node pointer

        // traverse until current->data == key
        while(curr && curr->name != countryName)
        {
            prev = prev->next;
            curr = curr->next;
        }

        // check if curr is not NULL
        if(!curr)
        {
            cout << "Country does not exist." << endl;
        } else {
            // rewiring and deleting
            prev->next = curr->next;
            delete curr;
        }
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    int num_countries = 6;
    string countries[] = {"United States", "Canada", "Brazil", "India", "China", "Australia"};
    // deleteEntireNetwork();
    Country* prev = NULL;
    for(int i = 0; i < num_countries; i++)
    {
        insertCountry(prev, countries[i]);
        prev = searchNetwork(countries[i]);
    }
}


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
// Search until the head is NULL, or we find the country
    Country* ptr = head;
    while (ptr != NULL && ptr->name != countryName)
    {
        ptr = ptr->next;
    }
    // Return the node, or NULL
    return ptr;
}

/*
* Purpose: Creates a loop from last node to the country specified.
* @param countryName name of the country to loop back
* returns pointer to last node before loop creation (to break the loop)
*/
Country* CountryNetwork::createLoop(string countryName)
{
    if(!head) { return nullptr; }

    Country* c = searchNetwork(countryName);
    Country* curr = head;
    while(curr->next != nullptr)
    {
        curr = curr->next;
    }
    curr->next = c;
    return curr;
}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
    //TODO: Complete this function

    if(!head) { return; }

    // setup pointers
    Country *prev = head;
    Country *curr = head->next;

    // traverse and delete 
    while(curr != NULL)
    {
        cout << "deleting: " << prev->name << endl;
        delete prev;
        prev = curr;
        curr = curr->next;
    }

    // delete last node
    cout << "deleting: " << prev->name << endl;
    delete prev;

    // rewire head node
    head = nullptr;

    cout << "Deleted network" << endl;
}

/*
*Purpose: to detect loop in the linkedlist
* @param
* returns true if loop is detected. Otherwise return false.
*/
bool CountryNetwork::detectLoop() {

    // using Floyd's Cycle Detection Algorithm
    // https://en.wikipedia.org/wiki/Cycle_detection#Floyd's_Tortoise_and_Hare
    // https://www.youtube.com/watch?v=MFOAbpfrJ8g

    if(!head) { return false; }

    Country* slow = head;
    Country* fast = head->next;

    while(slow != nullptr && fast != nullptr && fast->next != nullptr)
    {
        if(slow == fast) { return true; }
        fast = fast->next->next;
        slow = slow->next;
    }
    return false;
}

/*
* Purpose: Locate and return a node at a specific index
*@param: index
*@param: head
* returns Country* at index if found; otherwise, return nullptr
*/
Country* getNodeAtIndex(int index, Country* &head)
{
    int i = 0;

    if (!head) { return nullptr; }

    Country* curr = head;
    while(curr->next != nullptr)
    {
        if(i == index)
        {
            return curr;
        }
        curr = curr->next;
        i++;
    }

    if(i == index) // check last node
    {
        return curr;
    }

    return nullptr;
}

/*
* Purpose: Take the chunk of nodes from start index to end index
*          Move that chunk at the end of the List
*@param: start index
*@param: end index
* return none
*/
void CountryNetwork:: readjustNetwork(int start_index, int end_index)
{
    //TODO: Complete this function
    //cout << "start index: " << start_index << endl << "end index: " << end_index << endl;

    if(!head)
    {
        cout << "Linked List is Empty" << endl;
        return;
    }

    if (start_index > end_index)
    {
        cout << "Invalid indices" << endl;
        return;
    }

    int numNodes = 0;

    Country *curr = head;
    while(curr->next != nullptr)
    {
        numNodes++;
        curr = curr->next;
    }
    numNodes++; // needed to test for edge cases

    if(end_index > numNodes || end_index < 0)
    {
        cout << "Invalid end index" << endl;
        return;
    }

    if(!(end_index < numNodes-1))
    {
        cout << "Invalid end index" << endl;
        return;
    }

    if(start_index > numNodes || start_index < 0)
    {
        cout << "Invalid start index" << endl;
        return;
    }

    // assume input is well behaved now

    if(start_index == 0) // need to replace head node
    {
        Country* startNode = getNodeAtIndex(start_index, head);
        Country* endNode = getNodeAtIndex(end_index, head);
        Country* lastNode = getNodeAtIndex(numNodes - 1, head);
        Country* newHead = getNodeAtIndex(end_index + 1, head);

        lastNode->next = startNode; // fix old tail pointer to point to start of section
        endNode->next = nullptr; // fix new tail pointer to nullptr
        head = newHead; // fix head pointer
    } else {
        Country* startNode = getNodeAtIndex(start_index, head);
        Country* endNode = getNodeAtIndex(end_index, head);
        Country* lastNode = getNodeAtIndex(numNodes - 1, head);
        Country* prevNode = getNodeAtIndex(start_index - 1, head);
        Country* postNode = getNodeAtIndex(end_index + 1, head);

        lastNode->next = startNode; // loop end of list back to section
        endNode->next = nullptr; // fix last node to point to nullptr
        prevNode->next = postNode; // fix list after section removal
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
    cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    Country* ptr = head;
    if (ptr == NULL)
        cout << "nothing in path" << endl;

    // Otherwise print each node, and then a NULL
    else
    {
        while (ptr->next != NULL)
        {
            cout << ptr->name << " -> ";
            ptr = ptr->next;
        }
        cout << ptr->name << " -> ";
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
}
