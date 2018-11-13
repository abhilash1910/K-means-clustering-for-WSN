#include<stdio.h>
#include "Graph.h"
#include <vector>
#include <iostream>
#include <algorithm>
 
bool isSafe(int v, Graph* graph, const std::vector<int>& path, int pos)
{   
    if (!graph->hasEdge( path[pos - 1], v ))
        return false;
     
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;
 
    return true;
}
 
bool hamiltonianCycleUtility(Graph* graph, std::vector<int> path, int pos)
{   
    if (pos == graph->V())
    {       
        if (graph->hasEdge(path[pos - 1], path[0]))
        {
            graph->StorePath(path);
            return true;
        }
        else
        {
            return false;
        }
    }
     
    for (int v = 1; v < graph->V(); v++)
    {       
        if (isSafe(v, graph, path, pos))
        {
            path[pos] = v;
             
            if (hamiltonianCycleUtility(graph, path, pos + 1) == true)
            {                       
                return true;
            }
 
            // If adding vertex v doesn't lead to solution remove it
            path[pos] = -1;
        }
    }
 
    return false;
}
 
void PrintTour(Graph* graph)
{
    std::cout << "Hamiltonian tour exists: " << std::endl;
    graph->ShowPath();
    std::cout << std::endl;
}
 
bool IsHamiltonian(Graph* graph)
{
    std::vector<int> path(graph->V());
    std::transform(path.begin(), path.end(), 
        path.begin(), [](int n) -> int { return -1; } );
 
    path[0] = 0;
    if (hamiltonianCycleUtility(graph, path, 1) == false)
    {
        std::cout << "Solution does not exist" << std::endl;
        return false;
    }
     
    PrintTour(graph);
    return true;    
}
 
int main()
{
    //  Create the following graph
    //  (0)--(1)--(2)
    //  |          |
    //  |          |
    //  |          |
    //  (3)-------(4)       
    Graph g1(5, false);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 4);
    g1.addEdge(3, 4);
    g1.addEdge(0, 3);
     
    bool isHamiltonianTour = IsHamiltonian(&g1);
 
    //  Create the following graph
    //  (0)--(1)--(2)
    //  |          |
    //  |          |
    //  |          |
    //  (3)       (4)   
    Graph g2(5, false);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 4);   
    g2.addEdge(0, 3);
 
    isHamiltonianTour = IsHamiltonian(&g2);
 
    //  Create the following graphs
    //  (0)--(1)--(2)--(0)  
    //  (3)--(4)--(5)--(3)      
    Graph g3(6, false);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(3, 4);
    g3.addEdge(4, 5);
    g3.addEdge(3, 5);
 
    isHamiltonianTour = IsHamiltonian(&g3);
 
    return 0;
}
