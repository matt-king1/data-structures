#include <iostream>

using namespace std;

int main(){
    int a = 20;
    float b = 20.25;
    int *pa = &a;
    float *pb = &b;

    std::cout << sizeof(pa) << std::endl;
    std::cout << sizeof(pb) << std::endl;

    std::cout << "Hello World!" << std::endl;
}