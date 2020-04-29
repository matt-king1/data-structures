#include "hash.hpp"
#include "LL.hpp"
#include <fstream>
#include <vector>
#include <chrono>

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
    // TODO: Need to repeat tests with dataSetB
    int testDataA[40000];
    float insert[400];
    float search[400];

    string dataSetAFilename = argv[1];
    ifstream dataAFile(dataSetAFilename);
    string dataS;

    getline(dataAFile, dataS); // dataS now holds the entire contents of dataSetA.csv

    vector<string> stringVector = split(dataS, ',');
    vector<int> intVector;

    for (int i = 0; i < 40000; i++)
    {
        testDataA[i] = stoi(stringVector.at(i));
    }

    // /* *********************************************************************************************** \
    // \                                            Insert:                                              */
    // LinkedList LL;
    // auto start = std::chrono::steady_clock::now();
    // for (int i = 0; i < 100; i++)
    // {
    //     LL.insert(testDataA[i]);
    // }
    // auto end = std::chrono::steady_clock::now();
    // auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // time currently stores the time to insert 100 elements
    // cout << "Average time to insert an element in LL: " << time.count() / 100.0 << " microseconds" << endl;
    // insert[0] = time.count() / 100.0;

    // /* *********************************************************************************************** \
    // \                                            Search:                                              */

    // int random[100];
    // for (int i = 0; i < 100; i++)
    // {
    //     // populate random[] with random numbers in [0, 99]
    //     random[i] = rand() % 100;
    // }

    // start = std::chrono::steady_clock::now();
    // for (int i = 0; i < 100; i++)
    // {
    //     Node *t = LL.search(testDataA[random[i]]);
    // }
    // end = std::chrono::steady_clock::now();
    // time = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // time currently stores the time to search 100 elements
    // cout << "Average time to search an element in LL: " << time.count() / 100.0 << " microseconds" << endl;
    // search[0] = time.count() / 100.0;

    LinkedList LL;
    int random[100];
    for (int delta = 0; delta < 400; delta++)
    {
        auto start = std::chrono::steady_clock::now();
        for (int i = delta*100; i < delta*100+100; i++)
        {
            LL.insert(testDataA[i]);
        }
        auto end = std::chrono::steady_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // time currently stores the time to insert 100 elements
        cout << "Average time to insert an element in LL: " << time.count() / 100.0 << " microseconds" << endl;
        insert[delta] = time.count() / 100.0;

        for (int i = 0; i < 100; i++)
        {
            random[i] = rand() % (100 * (delta+1));
        }

        start = std::chrono::steady_clock::now();
        for (int i = 0; i < 100; i++)
        {
            Node *t = LL.search(testDataA[random[i]]);
        }
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // time currently stores the time to search 100 elements
        cout << "Average time to search an element in LL: " << time.count() / 100.0 << " microseconds" << endl;
        search[delta] = time.count() / 100.0;
    }

    for(int i = 0; i < 400; i++)
    {
        cout << search[i] << endl;
    }
    cout << "=======================" << endl;
    for(int i = 0; i < 400; i++)
    {
        cout << insert[i] << endl;
    }
}