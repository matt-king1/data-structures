#include "hash.hpp"
#include "LL.hpp"
#include <fstream>

int main(int argc, char** argv)
{
    LinkedList *ll = new LinkedList();
    string dataSetAFile = argv[1];
    ifstream dataAFile(dataSetAFile);
    string dataS;

    getline(dataAFile, dataS); // dataS now holds the entire contents of dataSetA.csv
}