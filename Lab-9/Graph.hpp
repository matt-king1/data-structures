#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

struct vertex;

struct adjVertex{
    vertex *v;
};

struct vertex{
    int key;
    bool visited = false;
    std::vector<adjVertex> adj;
};

class Graph
{
    public:
        void addEdge(int v1, int v2);
        void addVertex(int v);
        void printGraph();

    private:
        std::vector<vertex*> vertices;

};

#endif
