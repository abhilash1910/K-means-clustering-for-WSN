vector<pair<int,int> > veuler;
class Graph
{
  int V;
  list<int> *adj;
public:
     Graph(int V)  {
          this->V = V;
        adj = new list<int>[V];
         }

  ~Graph()
  { delete [] adj;
  }

  void addEdge(int u, int v) {
       adj[u].push_back(v);
        adj[v].push_back(u); }
  void rmvEdge(int u, int v);
  void printEulerTour();
  void printEulerUtil(int s);

  int DFSCount(int v, bool visited[]);

  bool isValidNextEdge(int u, int v);
};
void Graph::printEulerTour()
{
  int u = 0;
  for (int i = 0; i < V; i++)
      if (adj[i].size() & 1)
        {   u = i; break;  }

  printEulerUtil(u);
  cout << endl;
}

void Graph::printEulerUtil(int u)
{
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
  {
      int v = *i;

      if (v != -1 && isValidNextEdge(u, v))
      {
          cout << u << "-" << v << "  ";
          veuler.push_back(make_pair(u,v));
          rmvEdge(u, v);
          printEulerUtil(v);
      }
  }
}

bool Graph::isValidNextEdge(int u, int v)
{
   int count = 0;
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
     if (*i != -1)
        count++;
  if (count == 1)
    return true;


  bool visited[V];
  memset(visited, false, V);
  int count1 = DFSCount(u, visited);

  rmvEdge(u, v);
  memset(visited, false, V);
  int count2 = DFSCount(u, visited);

  addEdge(u, v);

  return (count1 > count2)? false: true;
}

void Graph::rmvEdge(int u, int v)
{
  list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
  *iv = -1;

  list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
  *iu = -1;
}

int Graph::DFSCount(int v, bool visited[])
{
  visited[v] = true;
  int count = 1;

  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
      if (*i != -1 && !visited[*i])
          count += DFSCount(*i, visited);

  return count;
}

int main()
{
cout<<"Euler path"<<endl;
  Graph g3(5);
  g3.addEdge(1, 0);
  g3.addEdge(0, 2);
  g3.addEdge(2, 1);
  g3.addEdge(0, 3);
  g3.addEdge(3, 4);
  g3.addEdge(3, 2);
  g3.addEdge(3, 1);
  g3.addEdge(2, 4);
  g3.printEulerTour();
  cout<<"vector of paths"<<endl;
int i;
for(i=0;i<veuler.size();i++)
{

    cout<<veuler[i].first<<""<<veuler[i].second<<endl;
}



  return 0;
}
