#include <list>  
#include <vector>
#include <memory>
 
class Graph
{
    int _V;    
    bool _directed;
    std::unique_ptr<std::list<int>> adj;    
    std::vector<int> pathstore;
 
public:
 
    Graph(int V, bool directed);
    void addEdge(int v, int w); 
    int V();
    bool hasEdge(int v, int w);
    void ShowPath();
    void StorePath(const std::vector<int>& path);
};
