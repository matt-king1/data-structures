#include "BST.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono> // timing library
#include <vector>

//
//  Author: Matt King
//  CSCI 2270 Final Project
//  Contribution: Wrote headers, implementations, drivers, and created figures for BST and LL. Also did writeup.
//

using namespace std;
const vector<string> split(const string &s, const char &c) // helper function to split s based on delimiter c
{
    string buff{""};
    vector<string> v;

    for (auto n : s)
    {
        if (n != c)
            buff += n;
        else if (n == c && buff != "")
        {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "")
        v.push_back(buff);

    return v;
}

int main(int argc, char **argv)
{
    int testDataA[40000];   // storage for data read from a testData file
    float insert[400];      // storage for average insertion times
    float search[400];      // storage for average search times

    string dataSetAFilename = argv[1];
    ifstream dataAFile(dataSetAFilename);
    string dataS;

    getline(dataAFile, dataS); // dataS now holds the entire contents of testData.csv

    vector<string> stringVector = split(dataS, ','); // split the csv into strings

    for (int i = 0; i < 40000; i++)
    {
        testDataA[i] = stoi(stringVector.at(i)); // parse int from string
    }

    BST bst; // data structure to test
    int random[100]; // array to hold random indices
    for (int delta = 0; delta < 400; delta++)
    {
        auto start = std::chrono::steady_clock::now(); // start time
        for (int i = delta*100; i < delta*100+100; i++)
        {
            bst.addNode(testDataA[i]); // add the first 100 test datums
        }
        auto end = std::chrono::steady_clock::now(); // end time
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // time currently stores the time to insert 100 elements
        // cout << "Average time to insert an element in LL: " << time.count() / 100.0 << " microseconds" << endl;
        insert[delta] = time.count() / 100.0; // add the average time to insert 1 element into the insert array at index delta

        for (int i = 0; i < 100; i++)
        {
            random[i] = rand() % (100 * (delta+1)); // populate the random array with numbers in [0, 99+(delta*100)]. This is the range of elements currently in the test data structure
        }

        start = std::chrono::steady_clock::now(); // start time for search
        for (int i = 0; i < 100; i++)
        {
            Node *t = bst.searchKey(testDataA[random[i]]); // search for 100 random elements guaranteed to be in the bst
        }
        end = std::chrono::steady_clock::now(); // end time for search
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // time currently stores the time to search 100 elements
        // cout << "Average time to search an element in LL: " << time.count() / 100.0 << " microseconds" << endl;
        search[delta] = time.count() / 100.0; // add the average time to search 1 element to the search array at index delta
    }

    ofstream outFile;
    string outputFilename = "insert_search_performance_bst_" + dataSetAFilename;
    outFile.open(outputFilename);
    outFile << "SEARCH TIMES: " << endl;
    for(int i = 0; i < 400; i++)
    {
        outFile << search[i] << endl;
    }
    outFile << "==================================" << endl;
    outFile << "INSERT TIMES: " << endl;
    for(int i = 0; i < 400; i++)
    {
        outFile << insert[i] << endl;
    }
}