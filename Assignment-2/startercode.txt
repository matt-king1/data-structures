#include <fstream>

// this is reference for reading a file word by word  (Can be used for reading both stop words and unique words)

ifstream inStream;      // stream for reading in file
inStream.open(filename); // open the file

string word;
while (inStream >> word ){

// get stop words / unique words into array

}
inStream.close(); // close the file
