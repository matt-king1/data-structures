#include <iostream>
#include <string>

using namespace std;

bool append(string* &str_arr, string s, int &numEntries, int &arraySize)
{
    if(numEntries == arraySize) //array at max capacity; we need to double
    {
        int newSize = 2 * arraySize;
        string* dbl = new string[newSize];

        for(int i = 0; i < arraySize; i++)
        {
            dbl[i] = str_arr[i];
        }

        delete[] str_arr;
        str_arr = dbl;
        arraySize = newSize;

        str_arr[numEntries] = s;
        numEntries++;

        return true;
    }

    str_arr[numEntries] = s;
    numEntries++;
    return false;
}

int main(int argc, char** argv)
{
    int numEntries = 0;
    int arraySize = 2;

    string* test = new string[arraySize];
    test[0] = "a";
    test[1] = "b";

    append(test, "e", numEntries, arraySize);
    append(test, "8==D", numEntries, arraySize);

    cout << numEntries << endl;
    cout << arraySize << endl;

    for(int i = 0; i < numEntries; i++)
    {
        cout << test[i] << endl;
    }
}