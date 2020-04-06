#include "Graph.hpp"
#include <stdio.h>
#include <queue>

void Graph::addVertex(string name)
{
    vertex* v = new vertex;
    v->name = name;
    v->visited = false;
    vertices.push_back(v);
}

void Graph::addEdge(string v1, string v2)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices.at(i)->name == v1)
        {
            for(int j = 0; j < vertices.size(); j++)
            {
                if(vertices.at(j)->name == v2)
                {
                    if(i != j)
                    {
                        adjVertex adjv1 = adjVertex{ vertices.at(i) };
                        adjVertex adjv2 = adjVertex{ vertices.at(j) };

                        vertices.at(i)->adj.push_back(adjv2);
                        vertices.at(j)->adj.push_back(adjv1);
                    }
                }
            }
        }
    }
}

void Graph::displayEdges()
{
    for(int i = 0; i < vertices.size(); i++)
    {
        vertex* v = vertices.at(i);
        cout << v->name << " --> ";

        for(int j = 0; j < v->adj.size(); j++)
        {
            cout << v->adj.at(j).v->name << " ";
        }

        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex)
{
    vertex* vStart = nullptr;

    for(vertex* v : vertices)
    {
        if(v->name == sourceVertex)
        {
            vStart = v;
        }
    }

    if(vStart == nullptr)
    {
        cout << "Root vertex not found" << endl;
        return;
    }

    cout << "Starting vertex (root): " << vStart->name << "-> ";

    queue<vertex*> q;

    vStart->visited = true;
    vStart->distance = 0;

    q.push(vStart);

    while(!q.empty())
    {
        vertex* curr = q.front();
        q.pop();

        for(int i = 0; i < curr->adj.size(); i++)
        {
            if(!(curr->adj.at(i).v->visited))
            {
                curr->adj.at(i).v->distance = curr->distance + 1;
                curr->adj.at(i).v->visited = true;

                cout << curr->adj.at(i).v->name << "(" << curr->adj.at(i).v->distance << ") ";
                q.push(curr->adj.at(i).v);
            }
        } 
    }
}

void DFS(vertex* start)
{
    if(start->visited == false)
    {
        start->visited = true;
        for(int i = 0; i < start->adj.size(); i++)
        {
            DFS(start->adj.at(i).v);
        }
    }
}

int Graph::getConnectedComponents()
{
    int count = 0;

    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices.at(i)->visited == false)
        {
            DFS(vertices.at(i));
            count += 1;
        }
    }

    return count;
}