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




    // TIMER CODE GIVEN DURING LECTURE

    /*

    #include <chrono>
    using namespace std::chrono;
    high_resolution_clock::time_point start = high_resolution_clock::now(); high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double> execTime = duration_cast<microseconds>(end - start); std::cout << "\nbubble execution time: " << execTime.count() << " seconds." <<  std::endl;

    */
}