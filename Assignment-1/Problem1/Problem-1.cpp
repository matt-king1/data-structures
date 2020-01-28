#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits.h>

using namespace std;

int insertIntoSortedArray(float myArray[], int numEntries, float newValue)
{
    if(numEntries == 0)
    {
        myArray[0] = newValue;
        return numEntries+1;
    }

    for(int i = 0; i <= numEntries; i++)
    {
        float val = myArray[i];
        if(newValue > val)
        {
            for(int j = numEntries; j >= i; j--)
            {
                myArray[j+1] = myArray[j];
            }
            myArray[i] = newValue;
            break;
        }
        else if(newValue < val) { continue; }
    }
    return numEntries + 1;
}


int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        std::cout << "Failed to open the file.";
        return 1;
    }

    float myArray[100] = {};

    for(int i = 0; i < 100; i++)
    {
        myArray[i] = INT_MIN;
    }

    int size = 0;

    // for(float i : myArray) { cout << i << " "; }

    // size = insertIntoSortedArray(myArray, size, -11);

    // for(float i : myArray) { cout << i << " "; }
    
    ifstream ifs(argv[1]);
    string line;

    if(!ifs.is_open()) { cout << "Failed to open the file."; }

    while(getline(ifs,line,'\n'))
    {
        float num = std::stof(line.c_str());
        size = insertIntoSortedArray(myArray, size, num);

        for(int i = 0; i < size; i++)
        {
            if(i < size-1)
            {
                cout << myArray[i] << ",";
            } else {
                cout << myArray[i];
            }
        }

        cout << endl;

        if (size >= 100) { break; }
    }

    ifs.close();
}