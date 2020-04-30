#include "hash.hpp"
#include "LL.hpp"
#include <fstream>
#include <vector>
#include <chrono>

//
//  Author: Matt King
//  CSCI 2270 Final Project
//

const vector<string> split(const string &s, const char &c)
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

    LinkedList LL; // data structure to test
    int random[100]; // array to hold random indices
    for (int delta = 0; delta < 400; delta++) // loop through 400 delta
    {
        auto start = std::chrono::steady_clock::now();
        for (int i = delta*100; i < delta*100+100; i++)
        {
            LL.insert(testDataA[i]);
        }
        auto end = std::chrono::steady_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // time currently stores the time to insert 100 elements
        // cout << "Average time to insert an element in LL: " << time.count() / 100.0 << " microseconds" << endl;
        insert[delta] = time.count() / 100.0;

        for (int i = 0; i < 100; i++)
        {
            random[i] = rand() % (100 * (delta+1)); // populate the random array with indices in [0, 99 + (100*delta)]
        }

        start = std::chrono::steady_clock::now();
        for (int i = 0; i < 100; i++)
        {
            Node *t = LL.search(testDataA[random[i]]); // search for elements guaranteed to be in the LL
        }
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // time currently stores the time to search 100 elements
        // cout << "Average time to search an element in LL: " << time.count() / 100.0 << " microseconds" << endl;
        search[delta] = time.count() / 100.0;
    }

    ofstream outFile;
    string outputFilename = "insert_search_performance_linked_list_" + dataSetAFilename; // insert_search_performance_linked_list_dataSetA.csv
    outFile.open(outputFilename);
    outFile << "SEARCH TIMES: " << endl;
    for(int i = 0; i < 400; i++)
    {
        outFile << search[i] << endl;
    }
    outFile << "==================================" << endl; // format output
    outFile << "INSERT TIMES: " << endl;
    for(int i = 0; i < 400; i++)
    {
        outFile << insert[i] << endl;
    }
}