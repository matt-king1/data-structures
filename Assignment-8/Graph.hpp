#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>
using namespace std;

struct vertex;
struct adjVertex{
    vertex *v;
};

struct vertex{

    string name;
    bool visited = false;
    int distance = 0;
    vector<adjVertex> adj;


};

class Graph
{
    public:
        void addEdge(string v1, string v2);
        void addVertex(string name);
        void displayEdges();
        void breadthFirstTraverse(string sourceVertex);
        int getConnectedComponents();


    private:
        vector<vertex*> vertices;
};

#endif // GRAPH_H
