/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
#include <string>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[])
{
	ProducerConsumer pc = ProducerConsumer();
	menu();

	string sinput, snum, sitem, titem;
	int input, num;
	int counter = 0;

	getline(cin, sinput);

	while(true)
	{
		input = stoi(sinput);
		
		if(input == 1)
		{
			// producer
			cout << "Enter the number of items to be produced: " << endl;
			getline(cin, snum);
			num = stoi(snum);
			for(int i = 0; i < num; i++)
			{
				cout << "Item" << i + 1 << ":" << endl;
				getline(cin, sitem);
				pc.enqueue(sitem);
				counter++;
			}
		}

		if(input == 2)
		{
			cout << "Enter the number of items to be consumed:" << endl;
			getline(cin, snum);
			num = stoi(snum);
			for(int i = 0; i < num; i++)
			{
				if(pc.isEmpty())
				{
					cout << "No more items to consume from queue" << endl;
					break;
				}
				titem = pc.peek();
				pc.dequeue();
				cout << "Consumed: " << titem << endl;
				counter--;
			}
		}

		if(input == 3)
		{
			cout << "Number of items in the queue:" << counter << endl;
			break;
		}

		menu();
		getline(cin, sinput);
	}
}
