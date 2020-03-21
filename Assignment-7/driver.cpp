#include <iostream>
#include <fstream>
#include <sstream>

#include "MovieTree.hpp"

using namespace std;

static const char *USAGE = " [filename]\n\
\tread movies from filename and build an interactive bst";

int main(int argc, char *argv[])
{
	ifstream dataFile;
	string dataLine;

	MovieTree movies;

	if (argc != 2)
	{
		cerr << argv[0] << USAGE << endl;
		return 1;
	}

	dataFile.open(argv[1]);

	if (!dataFile.is_open())
	{
		cerr << "Could not open " << argv[1] << " for reading!" << endl;
		return 2;
	}

	while (getline(dataFile, dataLine))
	{
		int ranking, releaseYear;
    float rating;
		string title;
		string datum;
		stringstream dataStream(dataLine);

		// ranking
		getline(dataStream, datum, ',');
		ranking = stoi(datum);

		// title
		getline(dataStream, title, ',');
		// cout << "Adding: " << title << endl;

		// releaseYear
		getline(dataStream, datum, ',');
		releaseYear = stoi(datum);

		// rating
		getline(dataStream, datum, ',');
		rating = stof(datum);

		movies.addMovie(ranking, title, releaseYear, rating);
	}

	bool quit = false;
	while (!quit)
	{
		int option;
		string inputLine;

		cout << "======Main Menu======" << endl;
		cout << "1. Delete a movie" << endl;
		cout << "2. Print the inventory" << endl;
    cout << "3. Left rotate the tree" << endl;
		cout << "4. Quit" << endl;

		getline(cin, inputLine);

		if (inputLine.length() != 1 || inputLine[0] < '0' 
			|| inputLine[1] > '4') {
			cerr << "Invalid option : " << inputLine << endl;
			continue;
		}

		option = stoi(inputLine);

		switch (option)
		{

			case 1:
			{
				std::string _title;
				cout << "Enter a movie title:" << endl;
				getline(cin, _title);
				movies.deleteMovie(_title);
				break;
			}
			case 2:
			{
				movies.printMovieInventory();
				movies.inorderTraversal();
				break;
			}
	    case 3:
			{
				cout<< "give the titleChar of the node:"<<endl;
				string nodename;
				getline(cin, nodename);
	      		TreeNode* rNode = movies.searchChar(nodename[0]);
				if (rNode)
					movies.leftRotation(rNode);
				else
					cout << "titleChar not found" << endl;

	      break;
			}
			case 4:
			{
				quit = true;
			}
	}
}

	cout << "Goodbye!" << endl;

	return 0;
}
