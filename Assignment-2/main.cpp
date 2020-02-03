#include <iostream>
#include <fstream>

using namespace std;

struct wordItem
{
    string word;
    int count;
};

void getStopWords(const char* ignoreWordFileName, string ignoreWords[])
{
    ifstream ignoreIFS(ignoreWordFileName);

    if(!ignoreIFS.is_open())
    {
        cout << "Failed to open " << ignoreWordFileName << endl;
    }

    string word;
    int index = 0;
    while (ignoreIFS >> word )
    {
        ignoreWords[index] = word;
        index++;
    }
    ignoreIFS.close(); // close the file
}

bool isStopWord(string word, string ignoreWords[])
{
    for(int i = 0; i < 50; i++)
    {
        if(ignoreWords[i] == word)
        {
            return true;
        }
    }
    return false;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length)
{
    int count = 0;
    for(int i = 0; i < length; i++)
    {
        count += uniqueWords[i].count;
    }
    return count;
}

void arraySort(wordItem uniqueWords[], int length)
{
    wordItem temp;
    for(int i = 0; i < length-1; i++)
    {
        for(int j = 0; j < length-i-1; j++)
        {
            if(uniqueWords[j].count < uniqueWords[j+1].count)
            {
                wordItem temp = uniqueWords[j];
                uniqueWords[j] = uniqueWords[j+1];
                uniqueWords[j+1] = temp;
            }
        }
    }
}

void printNext10(wordItem uniqueWords[], int N, int totalNumWords)
{
    for(int i = N; i < N+10; i++)
    {
        std::cout << fixed << setprecision(4) << (float)uniqueWords[i].count/(float)totalNumWords << " - " << uniqueWords[i].word << endl;
    }
}

wordItem* resize(wordItem* arrayPtr, int &capacity)
{
	//increase the capacity by two times
	int newCapacity = 2 * capacity;
    cout<<"Resizing from "<<capacity<<" to "<<newCapacity<<endl;

	//dynamically allocate an array of size newCapacity
	wordItem *newArray = new wordItem[newCapacity];

	//copy all data from oldArray to newArray
	for(int i = 0; i < capacity; i++)
	{
		newArray[i] = arrayPtr[i];
	}

	//free the memory associated with oldArray
	delete[] arrayPtr;

	capacity = newCapacity;

	//return the newArray
	return newArray;
}

bool isInUniqueWordsArr(string word, wordItem* uniqueWords, int len)
{
    for(int i = 0; i < len; i++)
    {
        if(uniqueWords[i].word == word)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{  
    if(argc != 4) 
    {
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
        return 1;
    }

    int N = stoi(argv[1]); //N
    string textFile = argv[2]; //TomSawyer.txt
    string ignoreFile = argv[3]; //ignoreWords.txt  

    string ignoreWords[50] = {};
    getStopWords(ignoreFile.c_str(), ignoreWords);
    
    int capacity = 100;
    wordItem* uniqueWords = new wordItem[capacity];

    ifstream textFileIFS(textFile);
    string word;
    int index = 0;
    int timesResized = 0;

    while (textFileIFS >> word )
    {
        if(index == capacity-1)
        {
            resize(uniqueWords, capacity);
            timesResized++;
        }

        cout << word << ": " << isStopWord(word, ignoreWords) << " " << isInUniqueWordsArr(word, uniqueWords, index) << endl;

        if(!isStopWord(word, ignoreWords) && !isInUniqueWordsArr(word, uniqueWords, index))
        {
            cout << "Creating WI and adding to array at index: " << index << endl;
            wordItem wi = {word, 1};
            uniqueWords[index] = wi;
            index++;
            cout << "done" << endl;
        } else if (!isStopWord(word, ignoreWords))
        {
            cout << "Looking for WI in array" << endl;
            for(int i = 0; i < index; i++)
            {
                if(uniqueWords[i].word == word)
                {
                    cout << "Found word, incrementing count" << endl;
                    uniqueWords[i].count++;
                    //break;
                }
            }
        }
    }
    cout << "DONE" << " " << index << endl;

    for(int i = 0; i < index; i++)
    {
        cout << i << " " << uniqueWords[i].word << ": " << uniqueWords[i].count;
    }

    textFileIFS.close(); // close the file
}