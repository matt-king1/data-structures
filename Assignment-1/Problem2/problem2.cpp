#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Park
{
    string parkname;
    string state;
    int area;
};

void addPark(Park parks[], string parkname, string state, int area, int length)
{
    Park newpark = {parkname, state, area};
    parks[length] = newpark;
}

void printList(const Park parks[], int length)
{
    for(int i = 0; i < length; i++)
    {
        Park park = parks[i];
        std::cout << park.parkname <<" [" << park.state << "] area: "<< park.area << std::endl;
    }
}

int main(int argc, char* argv[])
{
    int currentSize = 0;

    Park parks[100];

    if(argc != 5) 
    { 
        cout << "File error" << endl;
        return 1;
    }

    string inFileName = argv[1];
    string outFileName = argv[2];
    int lowerBound = stoi(argv[3]);
    int upperBound = stoi(argv[4]);

    ifstream ifs = ifstream(inFileName);
    
    string line;

    while(getline(ifs,line,'\n'))
    {
        istringstream ss(line);
        string token;
        string name;
        string state;
        int area;

        vector<string> r;

        while(getline(ss, token, ','))
        {
            r.push_back(token);
        }
        
        name = r[0];
        state = r[1];
        area = stoi(r[2]);

        addPark(parks, name, state, area, currentSize);
        currentSize++;
    }

    printList(parks, currentSize);
    ifs.close();

    ofstream ofs(outFileName, fstream::out);
    
    for(int i = 0; i < currentSize; i++)
    {
        Park p = parks[i];
        if(p.area >= lowerBound && p.area <= upperBound)
        {
            ofs << p.parkname << "," << p.state << "," << p.area << "\n";
        }
    }

    ofs.close();
    //return 1;
}