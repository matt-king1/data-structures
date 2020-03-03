#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void displayMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Query movies"<< endl;
    cout << "3. Print the inventory"<< endl;
    cout << "4. Average Rating of movies"<< endl;
    cout << "5. Print Movies at Distance k" << endl;
    cout << "6. Quit"<< endl;
}

int main(int argc, char** argv) {
    int input;

    // Tree
    MovieTree* tree = new MovieTree();

    ifstream iFile(argv[1]);
    string line;

    // Variables for each line
    int ranking;
    int year;
    float rating;
    string title;

    // File IO
    while(getline(iFile, line)) {
        stringstream ss(line);
        string field;

        int counter = 0;
        while(getline(ss, field, ',')) {
            if (counter == 0)
                ranking = stoi(field);
            else if (counter == 1)
                title = field;
            else if (counter == 2)
                year = stoi(field);
            else if (counter == 3)
                rating = stof(field);
            counter++;
        }
        tree->addMovieNode(ranking, title, year, rating);
    }

    displayMenu();
    cin >> input;

    while (1) {
        if (input == 1) {
            string movie_title;
            cout << "Enter title:" << endl;
            cin.ignore();
            getline(cin, movie_title);
            tree->findMovie(movie_title);
        }
        else if (input == 2){
            float query_rating;
            int query_year;
            cout << "Enter minimum rating:" << endl;
            cin.ignore();
            cin >> query_rating;
            cout << "Enter minimum year:" << endl;
            cin.ignore();
            cin >> query_year;
            tree->queryMovies(query_rating, query_year);

        }
        else if (input == 3){
            tree->printMovieInventory();
        }
        else if (input == 4){
            tree->averageRating();
        }
        else if (input == 5){
            int level_k;
            cout << "Enter Level k: " << endl;
            cin.ignore();
            cin >> level_k;
            tree->printLevelNodes(level_k);
        }
        else if (input == 6){
            cout << "Goodbye!" << endl;
            break;
        }
        displayMenu();
        cin >> input;
    }
    return 0;
}
