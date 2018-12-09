#include<bits/stdc++.h>
using namespace std;
float energyamplitude=70;
//"energy amplitude=70PJ/bit/m2"
float energyel=50;

float channelcapacity=34;
//cout<<"Channel capacity=34"<<endl;
float packetinforate;
float lengthofchannel=10;
//cout<<"length of channel =10"<<endl;

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
 /* cout<<"vector of paths"<<endl;
int i;
for(i=0;i<veuler.size();i++)
{

    cout<<veuler[i].first<<""<<veuler[i].second<<endl;
}
*/
int n=veuler.size();

cout<<"ANALYSIS OF ENERGY,RESIDUAL ENERGY,LIFETIME FOR DYNAMIC PACKET RATE IN SINGLE CLUSTER"<<endl;
cout<<"SINGLE CLUSTER ANALYSIS"<<endl;
cout<<"enter packet information rate"<<endl;
cin>>packetinforate;
cout<<"transmission time for x packets"<<endl;

float time=packetinforate*(lengthofchannel/channelcapacity);
cout<<time<<endl;
cout<<"For a sensor in amout of energy consumed =(Eamp^2 + Eele)*(x*(l/r))"<<endl;


float eachsensor=time*(energyamplitude+energyel);

cout<<eachsensor<<endl;



vector<float> a;
vector<float> b;
 n=veuler.size();
 int i;
float energy;
cout<<"assign energy to each packet"<<endl;
for(i=0;i<n;i++)
{

    cin>>energy;
    a.push_back(energy);
    b.push_back(energy);
}


cout<<"Average packet data of p clusters collection time"<<endl;

float averagetime=time* n;

cout<<averagetime<<endl;
//cout<<"Travel Time input form one node cluster to another"<<endl;
/*vector<float> c;
float avrtravel;
for(i=0;i<n-1;i++)
{
    c.push_back(avrtravel);

}
*/


cout<<"ANALYSIS OF DYNAMIC INFORMATION PACKET RATE FOR ONE CYCLE"<<endl;
cout<<"Collected information by other sensors in the average time span"<<endl;
int avrtime=(int)averagetime;
float rate=0.25;
int j;
for(j=0;j<avrtime;j++)

{int ct=0;

    for(i=0;i<n;i++)
    {

        if(a[i]>0)
        {
            ct++;
        }
    }




    if(ct>=1)

{time+= rate*j;
  cout<<"energy consumed in "<<j<<"round"<<endl;
  eachsensor=time*(energyamplitude+energyel);

cout<<eachsensor<<endl;
cout<<endl;

    for(i=0;i<n;i++)
    {
      a[i]-=eachsensor;

    }

  cout<<" residual energy left in "<<j<<"round"<<endl;
cout<<endl;
   for(i=0;i<n;i++)
   {

       cout<<a[i]<<" ";
   }
   cout<<endl;
   cout<<endl;

   cout<<"Lifetime of packets"<<endl;

    for(i=0;i<n;i++)
    {
        if(a[i]>0)
    {float xc=a[i];
    float xy=b[i];
    xc=xc/xy;
    cout<<xc<<" ";

    }
    cout<<endl;
    }


    cout<<endl;
}

else if(ct<0)
{

    break;
}



}









  return 0;
}

