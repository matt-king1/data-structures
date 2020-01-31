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

    }
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

}