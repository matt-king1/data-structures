#include <iostream>
#include <fstream>
#include <chrono> 
#include <cstdlib>
#include <vector>
#include "hash3.hpp"

using namespace std;
using namespace std::chrono;
int main() {

    // initialize class 
    HashTable setB(40009);
    string structName = "hashChain";

    int valArr[40000]; // create array of integrs that holds values from file

    double insert[400];
    double search[400];
    double colInsert[400];
    double colSearch[400];

    ifstream myFile;
    myFile.open("dataSetB.csv");

    srand(time(0)); 
    vector<int> searchVect; // create vector to store searches


    string number;
    int i = 0; // read in all the values from the value array
    while(getline(myFile, number, ',')) {
        valArr[i] = stoi(number);
        i++;
    }


    // insert values 100 at a time and measure the average time for each
    for(int i = 0; i < 400; ++i) {

        // next stopping place
        int s = (i * 100) + 100;
        
        auto startI = high_resolution_clock::now(); // begin timer

        for(int p = (i * 100); p < s; ++p) { // loop that gets the next 100 elements
            setB.insertItem(valArr[p]);
        }

        auto stopI = high_resolution_clock::now(); // stop timer
        auto durationI = duration_cast<microseconds>(stopI - startI); // calc difference
        double insertTime = durationI.count();

        insertTime = insertTime / 100.0; // divide value by 100
        insert[i] = insertTime;
        

        // find a 100 random numbers within the inserted data to search for
        for(int v = 0; v < 100; ++v) { // get 100 rand numbers for search
            int randNum = rand() % ( (i * 100) + 100);
            searchVect.push_back(valArr[randNum]); // insert num in the search vector
        }



        auto startS = high_resolution_clock::now();
        for(int n = 0; n < 100; ++n) {
            setB.searchItem(searchVect[n]);
        }
        auto stopS = high_resolution_clock::now(); // stop timer
        auto durationS = duration_cast<microseconds>(stopS - startS);
        double searchTime = durationS.count();

        searchTime = searchTime / 100.0;
        search[i] = searchTime;
        searchVect.clear();

        colInsert[i] = setB.getInsert();
        colSearch[i] = setB.getSearch();

    }

    // timer done -- now to write results into the output file


    string insert_Dst = "setB_insertionTimes.csv";
    string insert_endDst = structName + "_" + insert_Dst;
    
    ofstream insertOut;
    insertOut.open(insert_endDst);
    for(int i = 0; i < 400; ++i) {
        insertOut << insert[i] << endl;
    }
    insertOut.close();

    string search_Dst = "setB_searchTimes.csv";
    string search_endDst = structName + "_" + search_Dst;

    ofstream searchOut;
    searchOut.open(search_endDst);
    for(int i = 0; i < 400; ++i) {
        searchOut << search[i] << endl;
    }
    searchOut.close();

    string colFinal = "setB_collisions.csv";
    string collisionTot = structName + "_" + colFinal;
    ofstream outCol;
    outCol.open(collisionTot);
    outCol << "insertCollisions, searchCollisions" << endl;
    for(int m = 0; m < 400; ++m) {
        outCol << colInsert[m] << endl;
    }
    outCol << "=====================================" << endl;
    for(int y = 0; y < 400; ++y) {
        outCol << colSearch[y] << endl;
    }
    outCol.close();

    return 0;
}