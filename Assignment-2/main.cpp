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
    if(!ignoreIFS.is_open)
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