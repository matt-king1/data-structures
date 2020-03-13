#include <iostream>
#include <vector>
#include "Graph.hpp"

using namespace std;


int main()
{
    Graph g; // undirected and unweighted
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(1, 4);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(3, 4);
    g.addEdge(5, 6);

    
    // SILVER TODO : Complete the printGraph() function
    // Expected Format for printing (the vertices/adjacent vertices can be in any order):
    // 1 --> 2 3 4 
    // 2 --> 1 3 
    // 3 --> 1 2 4
    // 4 --> 1 3 5 6
    // 5 --> 4 6
    // 6 --> 4 5

    g.printGraph();


    return 0;
}
