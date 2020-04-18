#include "Graph.hpp"
#include <iostream>
#include <stack>
#include <limits.h>

using namespace std;
void Graph::addEdge(string v1, string v2, int num)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices.at(i)->name == v1)
        {
            for (int j = 0; j < vertices.size(); j++)
            {
                if (vertices.at(j)->name == v2)
                {
                    if (i != j)
                    {
                        adjVertex adjv1 = adjVertex{vertices.at(i), num};

                        adjVertex adjv2 = adjVertex{vertices.at(j), num};

                        vertices.at(i)->adj.push_back(adjv2);
                        vertices.at(j)->adj.push_back(adjv1);
                    }
                }
            }
        }
    }
}

void dfs(vertex *v)
{
    for (int i = 0; i < v->adj.size(); i++)
    {
        if (!(v->adj[i].v->visited))
        {
            v->adj[i].v->visited = true;
            cout << v->adj[i].v->name << " -> ";
            dfs(v->adj[i].v);
        }
    }
}

void Graph::depthFirstTraversal(string sourceVertex)
{
    vertex *vStart = nullptr;

    for (vertex *v : vertices)
    {
        if (v->name == sourceVertex)
        {
            vStart = v;
        }
    }

    if (vStart == nullptr)
    {
        cout << "Root vertex not found" << endl;
        return;
    }

    cout << vStart->name << " -> ";
    vStart->visited = true;
    vStart->distance = 0;

    dfs(vStart);

    cout << "DONE" << endl;
}

void relax(vertex *v)
{
    for (unsigned int i = 0; i < v->adj.size(); i++)
    {
        if (v->distance + v->adj[i].weight < v->adj[i].v->distance)
        {
            v->adj[i].v->distance = v->distance + v->adj[i].weight;
        }
    }
}

vertex *smallestUnvisitedNode(vector<vertex *> &vertices)
{
    int currMin = INT_MAX;
    vertex *curr;
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->distance < currMin)
        {
            currMin = vertices[i]->distance;
            curr = vertices[i];
        }
    }

    return (currMin == INT_MAX) ? nullptr : curr;
}

bool allVisited(vector<vertex *> &vertices)
{
    for (unsigned int i = 0; i < vertices.size(); i++)
        if (vertices[i]->visited == false)
            return false;

    return true;
}

void dfsAndRelax(vertex *v, vector<vertex *> &vertices)
{
    vertex *min = smallestUnvisitedNode(vertices);
    if (min != nullptr)
    {
        relax(min);
        dfsAndRelax(min, vertices);
    }
    else
    {
        return;
    }
}

void Graph::dijkstraTraverse(string start)
{
    vertex *vStart = nullptr;

    for (vertex *v : vertices)
    {
        if (v->name == start)
        {
            vStart = v;
        }
    }

    if (vStart == nullptr)
    {
        cout << "Start vertex not found" << endl;
        return;
    }

    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i]->distance = 999;
        vertices[i]->visited = false;
    }

    vStart->visited = true;
    vStart->distance = 0;

    vector<vertex *> solved;
    solved.push_back(vStart);

    bool allSolved = false;
    int num = 0;

    while (!allSolved && num < 100)
    {
        num++;
        int min = 99999;
        vertex *v = nullptr;
        allSolved = true;

        for (int i = 0; i < solved.size(); i++)
        {
            vertex *s = solved[i];

            for (int j = 0; j < s->adj.size(); j++)
            {
                if (!(s->adj[j].v->visited))
                {
                    int distance = s->distance + s->adj[j].weight;

                    if (distance < min)
                    {
                        v = s->adj[j].v;
                        v->distance = distance;
                        min = distance;
                    }
                    allSolved = false;
                }
            }
        }
    }
}

void Graph::shortestPath(string start, string end)
{
    vector<vertex *> solved;
    vector<vertex *> path;
    vertex *endVert;
    int minDist = 99999;

    for (int i = 0; i < vertices.size(); i++)
    {
        vertex *tmpV = vertices[i];
        tmpV->visited = false;
        tmpV->pred = NULL;
        tmpV->distance = 99999;

        if (tmpV->name == start)
        {
            tmpV->distance = 0;
            tmpV->visited = true;
            solved.push_back(tmpV); // ensure all vertices are in the correct start state
        }

        if (tmpV->name == end)
            endVert = tmpV;
    }

    vertex* minVisited;
    vertex* minUnvisited;


    vertex* vert, *vis;
    while(endVert->visited == false)
    {
        minDist = 99999;

        for(int i = 0; i < solved.size(); i++)
        {
            vert = solved[i];

            for(int j = 0; j < vert->adj.size(); j++)
            {
                vis = vert->adj[j].v;
                if(vis->visited == false)
                {
                    vis->distance = vert->distance + vert->adj[j].weight;

                    if(vis->distance < minDist)
                    {
                        minDist = vis->distance;
                        minVisited = vis;
                        minUnvisited = vert;
                    }
                }
            }
        }

        solved.push_back(minVisited);
        minVisited->distance = minDist;

        minVisited->pred = minUnvisited;
        minVisited->visited = true;
    }

    path.push_back(minVisited);
    while(minVisited->pred != NULL)
    {
        minVisited = minVisited->pred;
        path.push_back(minVisited);
    }

    for(int i = path.size() - 1; i >= 0; i--)
    {
        cout << path.at(i)->name << " -> ";
    }
    cout << "DONE " << "[" << minDist << "]" << endl;
}