#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <iterator>  
 
Graph::Graph(int V, bool directed) : adj(new std::list<int>[V])
{
    _V = V;
    _directed = directed;       
}   
 
void Graph::addEdge(int v, int w)
{
    std::list<int>* adjacency = adj.get();
    adjacency[v].push_back(w);
 
    if (!_directed)
    {
        adjacency[w].push_back(v);
    }
}
 
int Graph::V() 
{ 
    return _V; 
}
 
bool Graph::hasEdge(int v, int w)
{
    std::list<int> adjList = (adj.get())[v];
    std::list<int>::iterator findIt = std::find(adjList.begin(), adjList.end(), w);   
    return findIt != adjList.end();
}
 
void Graph::ShowPath()
{   
    std::vector<int>::const_iterator start = pathstore.begin();
    std::vector<int>::const_iterator end = pathstore.end();
 
    if (start != end)
    {
        std::for_each(start, end, [](const int& n){ std::cout << n << " "; });
        std::cout << *start;
    }   
}
 
void Graph::StorePath(const std::vector<int>& path)
{ 
    pathstore = path;   
}
